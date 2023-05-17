/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:27:22 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/17 17:23:30 by rrasezin         ###   ########.fr       */
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
		id = fork();
		if (id == 0)
			ft_execute(table, env);
		waitpid(id, &status, 0);
		err = WEXITSTATUS(status);
	}
	else
		ft_execute(table, env);
	return (err);
}

int	execute_commande(t_table *table, t_env **env, int i) // 20 line
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
		err = ft_unset(table, env);
	else if (ft_strncmp("exit", table->commend, -1) == 0)
		err = ft_exit(table, env);
	else
		return (execute_cmd(table, env, i));
	return (err);
}

void	cmd_in_parent(t_table *table, t_env **env, int *executed)
{
	if (ft_strcmp(table->commend, "unset") == 0)
		exit_status = execute_commande(table, env, 0);
	else if (ft_strcmp(table->commend, "cd") == 0)
		exit_status = execute_commande(table, env, 0);
	else if (ft_strcmp(table->commend, "export") == 0 && table->arg[0] != NULL)
	{
		*executed = 1;
		exit_status = execute_commande(table, env, 0);
	}
}

void	simple_cmd(t_tree *tree, t_env **env, int executed, int id) // 24 line
{
	int	status;
	
	status = 0;
	if (tree->table->next[0] == 0)
		exit_status = execute_commande(tree->table, env, 0);
	else
	{
		get_here_docs(tree, *env);
		if (tree->table->commend)
			cmd_in_parent(tree->table, env, &executed);
		id = fork();
		if (id == 0)
		{
			redirection(tree->table);
			if (executed == 0 && tree->table->commend)
			{
				status = execute_commande(tree->table, env, 1);
				exit(status);
			}
			exit(exit_status);
		}
		waitpid(id, &status, 0);
		exit_status = WEXITSTATUS(status);
	}
}

void	execution(t_tree *tree, t_env **env) // 25 line
{
	int	id;
	int	status;

	id = 0;
	if (tree->type == 0)
		simple_cmd(tree, env,0, 0);
	else 
	{
		id = fork(); 
		if (id == 0)
		{
			get_here_docs(tree, *env);
			exit_status = pipex(tree, env);
			exit(exit_status);
		}
		waitpid(id, &status, 0);
		exit_status = WEXITSTATUS(status);
		if (exit_status == 105)
		{
			write (2, "minishell: fork: Resource temporarily unavailable\n", 50);
			exit_status = 1;
		}
	}
	new_env_var(env, sp_strjoin("?=", ft_itoa(exit_status), 1), 2);
	return ;
}
