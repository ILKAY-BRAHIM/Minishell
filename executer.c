/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:27:22 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/19 17:15:39 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin/builting.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

// norm 25 line : ----> ok
// nb function : -----> 5
// tester : ----------> ok

int	execute_cmd(t_table *table, t_env **env, int i)
{
	int	id;
	int	status;
	int	err;

	err = 0;
	if (i == 0)
	{
		// signal(SIGINT, SIG_IGN);
		id = fork();
		if (id == 0)
		{
			// signal(SIGINT, SIG_DFL);
			ft_execute(table, env);
		}
		waitpid(id, &status, 0);
		status += 128;
		err = WEXITSTATUS(status);
	}
	else
		ft_execute(table, env);
	return (err);
}

int	execute_commande(t_table *table, t_env **env, int i)
{
	int	err;

	err = 0;
	if (ft_strncmp("echo", table->commend, -1) == 0)
		err = ft_echo(table, env);
	else if (ft_strncmp("env", table->commend, -1) == 0)
		err = ft_env(table, env);
	else if (ft_strncmp("cd", table->commend, -1) == 0)
		err = ft_cd(table, env);
	else if (ft_strncmp("export", table->commend, -1) == 0)
		err = ft_export(table, env);
	else if (ft_strncmp("pwd", table->commend, -1) == 0)
		err = ft_pwd(table, env);
	else if (ft_strncmp("unset", table->commend, -1) == 0)
		err = ft_unset(table, env, 0);
	else if (ft_strncmp("exit", table->commend, -1) == 0)
		err = ft_exit(table, env);
	else
		return (execute_cmd(table, env, i));
	return (err);
}

void	cmd_in_parent(t_table *table, t_env **env, int *executed)
{
	if (ft_strcmp(table->commend, "unset") == 0)
		g_exit = execute_commande(table, env, 0);
	else if (ft_strcmp(table->commend, "cd") == 0)
		g_exit = execute_commande(table, env, 0);
	else if (ft_strcmp(table->commend, "export") == 0 && table->arg[0] != NULL)
	{
		*executed = 1;
		g_exit = execute_commande(table, env, 0);
	}
}

void	simple_cmd(t_tree *tree, t_env **env, int executed, int id)
{
	int	status;

	status = 0;
	if (tree->table->next[0] == 0)
		g_exit = execute_commande(tree->table, env, 0);
	else
	{
		get_here_docs(tree, *env);
		if (tree->table->commend)
			cmd_in_parent(tree->table, env, &executed);
		// signal(SIGINT, SIG_IGN);
		id = fork();
		if (id == 0)
			red_smp_cmd(tree->table, env, executed);
		waitpid(id, &status, 0);
		status += 128;
		g_exit = WEXITSTATUS(status);
	}
}

void	execution(t_tree *tree, t_env **env)
{
	int	id;
	int	status;

	id = 0;
	if (tree->type == 0)
		simple_cmd(tree, env, 0, 0);
	else
	{
		// signal(SIGINT, SIG_IGN);
		id = fork();
		if (id == 0)
			ex_here_docs(tree, env);
		waitpid(id, &status, 0);
		status += 128;
		g_exit = WEXITSTATUS(status);
		if (g_exit == 105)
		{
			write (2, "minishell: fork: Resource temporarily unavailable\n", 50);
			g_exit = 1;
		}
	}
	new_env_var(env, sp_strjoin("?=", ft_itoa(g_exit), 1), 2);
	return ;
}
