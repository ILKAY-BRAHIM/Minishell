/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:56:04 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/10 13:12:59 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"
#include <fcntl.h>
#include "unistd.h"

int	count_pipe(t_tree *tree)
{
	int	size;
	
	size = 1;
	while (tree->type == 1)
	{
		size++;
		tree = tree->right;
	}
	return (size);
}

int	pipex(t_tree *tree, t_env *env)
{
	int	p_1[2];
	int	p_2[2];
	int	*id;
	int	i;
	int j;
	int	size;
	int	status = 0;

	i = 0;
	j = 0;
	size = count_pipe(tree);
	id = ft_calloc(sizeof(int), size);
	pipe(p_1);
	while (tree->type == 1)
	{
		id[i] = fork();
		if (id[i] < 0)
		{
			while (j < i)
				waitpid(id[j++], &status, 0);
			exit(105);
		}
		if (id[i] == 0)
		{
			usleep(150 * size);
			if (i == 0)
			{
				close(p_1[0]);
				dup2(p_1[1], STDOUT_FILENO); //write
				if (tree->left->table->next[0] != 0)
					redirection(tree->left->table, env);
			}
			else if (i % 2 != 0)
			{
				close(p_2[0]);
				close(p_1[1]);
				dup2(p_1[0], STDIN_FILENO); //read
				dup2(p_2[1], STDOUT_FILENO); //write
				if (tree->left->table->next[0] != 0)
					redirection(tree->left->table, env);
			}
			else if (i % 2 == 0)
			{
				close(p_2[1]);
				close(p_1[0]);
					dup2(p_2[0], STDIN_FILENO); //read
					dup2(p_1[1], STDOUT_FILENO); //write
				if (tree->left->table->next[0] != 0)
					redirection(tree->left->table, env);
			}
			exit (execute_commande(tree->left->table, env, 1));
		}
		if (i == 0)
			pipe(p_2);
		else if (i % 2 != 0)
		{
			close(p_1[0]);
			close(p_1[1]);
			pipe(p_1);
		}
		else if (i % 2 == 0)
		{
			close(p_2[0]);
			close(p_2[1]);
			pipe(p_2);
		}
		tree = tree->right;
		i++;
	}

	if (id[i-1] != 0)
	{
		id[i] = fork();
		if (id[i] == 0)
		{
			if (i % 2 != 0)
			{
				close(p_2[0]);
				close(p_2[1]);
				close(p_1[1]);
				dup2(p_1[0], STDIN_FILENO);
				if (tree->table->next[0] != 0)
					redirection(tree->table, env);
				execute_commande(tree->table, env, 1);
			}
			else if(i % 2 == 0)
			{
				close(p_1[0]);
				close(p_1[1]);
				close(p_2[1]);
				dup2(p_2[0], STDIN_FILENO);
				if (tree->table->next[0] != 0)
					redirection(tree->table, env);
				execute_commande(tree->table, env, 1);
			}
		}
		close(p_1[0]);
		close(p_2[0]);
		close(p_1[1]);
		close(p_2[1]);
		i = 0;
		while (i < size)
		{
			waitpid(id[i], &status, 0);
			i++;
		}
	}
	return (WEXITSTATUS(status));
}