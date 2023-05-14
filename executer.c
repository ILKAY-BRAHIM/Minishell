/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:27:22 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/14 16:12:30 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin/builting.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int	execute_commande(t_table *table, t_env **env, int i)
{
	int	err;
	int	id;
	int	status;
	(void)i;
	err = 0;
	if (ft_strncmp("echo", table->commend, -1) == 0)
		err = ft_echo(table, *env);
	else if (ft_strncmp("env", table->commend, -1) == 0)
		err = ft_env(table, *env);
	else if (ft_strncmp("cd", table->commend, -1) == 0)
		err = ft_cd(table, *env);
	else if (ft_strncmp("export", table->commend, -1) == 0)
		err = ft_export(table, *env);
	else if (ft_strncmp("pwd", table->commend, -1) == 0)
		err = ft_pwd(table, *env);
	else if (ft_strncmp("unset", table->commend, -1) == 0)
		err = ft_unset(table, env);
	else if (ft_strncmp("exit", table->commend, -1) == 0)
		err = ft_exit(table, *env);
	else
	{
		if (i == 0)
		{
			id = fork();
			if (id == 0)
				ft_execute(table, *env);
			waitpid(id, &status, 0);
			err = WEXITSTATUS(status);
		}
		else
			ft_execute(table, *env);
	}
	return (err);
}


void	execution(t_tree *tree, t_env **env)
{
	int	i;
	int	id;
	int	status;
	int	ok;

	i = 0;
	id = 0;
	ok = 0;
	if (tree->type == 0)
	{
		if (tree->table->next[0] == 0)
			exit_status = execute_commande(tree->table, env, 0);
		else
		{
			get_here_docs(tree, *env);
			if (tree->table->commend)
			{	
				if (ft_strcmp(tree->table->commend, "unset") == 0)
					exit_status = execute_commande(tree->table, env, 0);
				else if (ft_strcmp(tree->table->commend, "cd") == 0)
					exit_status = execute_commande(tree->table, env, 0);
				else if (ft_strcmp(tree->table->commend, "export") == 0 && tree->table->arg[0] != NULL)
				{
					ok = 1;
					exit_status = execute_commande(tree->table, env, 0);
				}
			}
			id = fork();
			if (id == 0)
			{
				redirection(tree->table);
				if (ok == 0 && tree->table->commend)
				{
					status = execute_commande(tree->table, env, 1);
					exit(status);
				}
				exit(exit_status);
			}
			waitpid(id, &status, 0);
			exit_status = WEXITSTATUS(status);
			// exit_status = execute_commande(tree->table, env, 0);//most close the file descriptor
		}
	}
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
	new_env_var(*env, ft_strjoin("?=", ft_itoa(exit_status)), 2);
	// write (2, ft_itoa(exit_status), ft_strlen(ft_itoa(exit_status)));
	// write (2, "\n", 1);
	// free_tree(tree); need to code it     ("_")      !!!
	return ;
}

// int main()
// {
// 	t_tree *tree;
// 	t_table *table;
// 	t_env	*env;

// 	tree = calloc(sizeof(t_tree), 1);
// 	tree->type = 0;
// 	table = calloc(1, sizeof(t_table));
// 	table->commend = ft_strdup("echo");
// 	table->option = ft_split("-n -k", ' ');
// 	table->arg = ft_split("hello world", ' ');
// 	table->next = calloc(1, sizeof (int));
// 	tree->table = table;
	
// 	execution(tree, env);
// }