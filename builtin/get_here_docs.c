/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_docs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:04:46 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/13 13:23:31 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"
#include <fcntl.h>

char	*remouve_char(char *str, char c)
{
	int		size;
	int		i;
	char	*result;

	i = 0;
	size = 0;
	if (!str)
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] != c)
			size++;
		i++;
	}
	result = ft_calloc(size + 1, sizeof(char));
	i = 0;
	size = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c)
			result[size++] = str[i];
		i++;
	}
	free(str);
	return (result);
}

void	here_doc(t_env *env, int output, char *end, int expand)
{
	char	*read;
	char	*result;
	char	*exp;

	result = ft_calloc(1, 1);
	while (1)
	{
		read = readline("> ");
		if (!read)
			break;
		add_history(read);
		if (ft_strcmp(read , end) == 0)
		{
			free(read);
			break ;
		}
		if (expand == 1 && ft_strchr(read, '$') != NULL)
		{
			exp = ft_strdup(read);
			free(read);
			read = expanding(exp, env);
			read = remouve_char(read, '`');
			free(exp);
		}
		result = sp_strjoin(result, read, 2);
		result = sp_strjoin(result, "\n", 0);
	}
	fd_putstr(result, output);
	free(result);
}

void	get_here_docs(t_tree *tree, t_env *env)
{
	t_tree	*tmp;
	int		i;
	int	herdoc;
	int	id;
	int status;

	tmp = tree;
	while (tmp->type == 1)
	{
		i = 0;
		while(tmp->left->table->next[i] != 0)
		{
			if (tmp->left->table->next[i] == HERE_DOC || tmp->left->table->next[i] == HERE_DOC_EX)
			{
				id = fork();
				if (id == 0)
				{
					herdoc = open("/tmp/heredoc_", O_CREAT | O_TRUNC | O_RDWR, 0644);
					here_doc(env, herdoc, tmp->left->table->files[i], tmp->left->table->next[i]);
					close(herdoc);
					exit(0);
				}
				free(tmp->left->table->files[i]);
				tmp->left->table->files[i] = ft_strdup("/tmp/heredoc_");
				waitpid(id, &status, 0);
			}
			i++;
		}
		tmp = tmp->right;
	}
	i = 0;
	while(tmp->table->next[i] != 0)
	{
		if (tmp->table->next[i] == HERE_DOC || tmp->table->next[i] == HERE_DOC_EX)
		{
			id = fork();
			if (id == 0)
			{
				herdoc = open("/tmp/heredoc_", O_CREAT | O_TRUNC | O_RDWR, 0644);
				here_doc(env, herdoc, tmp->table->files[i], tmp->table->next[i]);
				close(herdoc);
				exit(0);
			}
			free(tmp->table->files[i]);
			tmp->table->files[i] = ft_strdup("/tmp/heredoc_");
			waitpid(id, &status, 0);
		}
		i++;
	}
}