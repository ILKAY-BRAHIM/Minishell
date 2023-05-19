/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:44:34 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/19 19:37:47 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_left(t_tree *tree)
{
	int	i;

	i = 0;
	free(tree->left->table->commend);
	while (tree->left->table->option[i])
		free(tree->left->table->option[i++]);
	free (tree->left->table->option);
	i = 0;
	while (tree->left->table->arg[i])
		free(tree->left->table->arg[i++]);
	free(tree->left->table->arg);
	i = 0;
	while (tree->left->table->files[i])
		free(tree->left->table->files[i++]);
	free(tree->left->table->files);
	free(tree->left->table->next);
	free(tree->left->table);
	free(tree->left);
}

void	free_right(t_tree *tree)
{
	int	i;

	i = 0;
	free(tree->table->commend);
	while (tree->table->option[i])
		free(tree->table->option[i++]);
	free(tree->table->option);
	i = 0;
	while (tree->table->arg[i])
		free(tree->table->arg[i++]);
	free(tree->table->arg);
	i = 0;
	while (tree->table->files[i])
		free(tree->table->files[i++]);
	free(tree->table->files);
	free(tree->table->next);
	free(tree->table);
}

void	free_tree(t_tree *tree)
{
	int		i;
	t_tree	*tmp;
	int		x;

	x = 0;
	while (1)
	{
		i = 0;
		if (tree->type == 1)
			free_left(tree);
		else
			free_right(tree);
		tmp = tree;
		tree = tree->right;
		free(tmp);
		if (tree == NULL)
			break ;
		x++;
	}
	free(tree);
}

int	main(int argc, char **argv, char **origin_env)
{
	t_tree	*tree;
	t_env	*env;
	t_token	*lst;
	char	*line;

	(void)argc;
	(void)argv;
	env = init_env(origin_env);
	while (1)
	{
		handell_sig();
		line = get_prompt();
		if (line != NULL)
		{
			lst = parsing_v3(line, env, 1);
			if (lst != NULL)
			{
				tree = lexer(lst, 0, lst);
				free_lst(lst);
				execution(tree, &env);
				free_tree(tree);
			}
			free(line);
		}
	}
}
