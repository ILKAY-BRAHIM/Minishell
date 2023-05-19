/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/06 11:56:04 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/19 19:37:29 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

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

void	redirect_result(t_tree *tree, t_pipe *p)
{
	if (p->i == 0)
	{
		close(p->p_1[0]);
		dup2(p->p_1[1], STDOUT_FILENO);
		if (tree->left->table->next[0] != 0)
			redirection(tree->left->table);
	}
	else if (p->i % 2 != 0)
	{
		close(p->p_2[0]);
		close(p->p_1[1]);
		dup2(p->p_1[0], STDIN_FILENO);
		dup2(p->p_2[1], STDOUT_FILENO);
		if (tree->left->table->next[0] != 0)
			redirection(tree->left->table);
	}
	else if (p->i % 2 == 0)
	{
		close(p->p_2[1]);
		close(p->p_1[0]);
		dup2(p->p_2[0], STDIN_FILENO);
		dup2(p->p_1[1], STDOUT_FILENO);
		if (tree->left->table->next[0] != 0)
			redirection(tree->left->table);
	}
}

void	execute_last_cmd(t_tree *tree, t_pipe *p, t_env **env)
{
	signal(SIGQUIT, SIG_DFL);
	if (p->i % 2 != 0)
	{
		close(p->p_2[0]);
		close(p->p_2[1]);
		close(p->p_1[1]);
		dup2(p->p_1[0], STDIN_FILENO);
		if (tree->table->next[0] != 0)
			redirection(tree->table);
		execute_commande(tree->table, env, 1);
	}
	else if (p->i % 2 == 0)
	{
		close(p->p_1[0]);
		close(p->p_1[1]);
		close(p->p_2[1]);
		dup2(p->p_2[0], STDIN_FILENO);
		if (tree->table->next[0] != 0)
			redirection(tree->table);
		execute_commande(tree->table, env, 1);
	}
}

void	execute_firsts_cmd(t_tree *tree, t_env **env, t_pipe *p)
{
	signal(SIGINT, SIG_IGN);
	p->id[p->i] = fork();
	if (p->id[p->i] < 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		while (p->j < p->i)
			waitpid(p->id[p->j++], &(p->status), 0);
		exit(105);
	}
	if (p->id[p->i] == 0)
	{
		redirect_result(tree, p);
		exit (execute_commande(tree->left->table, env, 1));
	}
	close_open_pipe(p);
}

int	pipex(t_tree *tree, t_env **env)
{
	t_pipe	p;

	p.i = 0;
	p.j = 0;
	p.status = 0;
	p.size = count_pipe(tree);
	p.id = ft_calloc(sizeof(int), p.size);
	pipe(p.p_1);
	while (tree->type == 1)
	{
		execute_firsts_cmd(tree, env, &p);
		tree = tree->right;
	}
	if (p.id[p.i - 1] != 0)
	{
		signal(SIGINT, SIG_IGN);
		p.id[p.i] = fork();
		if (p.id[p.i] == 0)
			signal(SIGINT, SIG_DFL);
		if (p.id[p.i] == 0)
			execute_last_cmd(tree, &p, env);
		close_parent_pipe(&p);
	}
	p.status += 128;
	return (WEXITSTATUS(p.status));
}
