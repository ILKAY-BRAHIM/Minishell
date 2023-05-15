/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:44:34 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/15 23:54:16 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tree(t_tree *tree)
{
	int i;
	t_tree *tmp;
	int x = 0;
	while (1 )
	{
		i = 0;
		if (tree->type == 1)
		{
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
		else
		{
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
		// free(tree);
		tmp = tree;
		tree = tree->right;
		free(tmp);
		if (tree == NULL)
			break ;
		x++;
	}
	free(tree);
}




void	print_tree(t_tree *tree)
{
	int i;
	int x = 0;
	while (1 )
	{
		i = 0;
		if (tree->type == 1)
		{
			printf("TYPE : pipe\n");
			printf("CMD : |%s|\n", tree->left->table->commend);
			while (tree->left->table->option[i])
			{
				printf("OPTION : |%s|\n", tree->left->table->option[i]);
				i++;
			}
			i = 0;
			while (tree->left->table->arg[i])
			{
				printf("ARG : |%s|\n", tree->left->table->arg[i]);
				i++;
			}
			i = 0;
			while (tree->left->table->files[i])
			{
				printf("FILES : |%s|\n", tree->left->table->files[i]);
				if (tree->left->table->next[i] != 0)
					printf("REDIRECTION : |%d|\n", tree->left->table->next[i]);
				i++;
			}
		}
		else
		{
			printf("CMD : |%s|\n", tree->table->commend);
			while (tree->table->option[i])
			{
				printf("OPTION : |%s|\n", tree->table->option[i]);
				i++;
			}
			i = 0;
			while (tree->table->arg[i])
			{
				printf("ARG : |%s|\n", tree->table->arg[i]);
				i++;
			}
			i = 0;
			int j = 0;
			while (tree->table->files[i])
			{
				printf("FILES : |%s|\n", tree->table->files[i]);
				while (tree->table->files[i][j])
				{
					if (tree->table->files[i][j] == '\7')
						printf("---- : 7\n");
					if (tree->table->files[i][j] == '\6')
						printf("---- : 6\n");
					if (tree->table->files[i][j] == '\1')
						printf("---- : 1\n");
						j++;
				}
				if (tree->table->next[i] != 0)
					printf("REDIRECTION : |%d|\n", tree->table->next[i]);
				i++;
			}
		}
		tree = tree->right;
		if (tree == NULL)
			break ;
		x++;
	}
}

int main(int argc, char **argv, char **origin_env)
{
	t_tree	*tree;
	t_env	*env;
	t_token	*lst;
	char	*line;
	int		i;

	(void)argc;
	(void)argv;
	env = init_env(origin_env);
	while (1)
	{
		// handell_sig();
		i = 0;
		line = get_prompt();
		if (line != NULL)
		{
			lst = parsing_v3(line, env);
			if (lst != NULL)
			{
				tree = lexer(lst);
				free_lst(lst);
				// print_tree(tree);
				execution(tree, &env);
				free_tree(tree);
			}
		}
		if (line)
			free (line);
	}
}
