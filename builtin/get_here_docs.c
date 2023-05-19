/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_here_docs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 12:04:46 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/19 19:37:17 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"
#include <fcntl.h>
#include <sys/wait.h>

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

void	exp_here_doc(t_env *env, char **read)
{
	char	*exp;

	exp = ft_strdup(*read);
	free(*read);
	*read = expanding(exp, env);
	*read = remouve_char(*read, '`');
	free(exp);
}

void	here_doc(t_env *env, int output, char *end, int expand)
{
	char	*read;
	char	*result;

	result = ft_calloc(1, 1);
	while (1)
	{
		read = readline("> ");
		if (!read || (read[0] == '\0'
				&& ft_strlen(end) == 2 && end[0] == '\1' && end[1] == '\1'))
			break ;
		add_history(read);
		if (ft_strcmp(read, end) == 0)
		{
			free(read);
			break ;
		}
		if (expand == 1 && ft_strchr(read, '$') != NULL)
			exp_here_doc(env, &read);
		result = sp_strjoin(result, read, 2);
		result = sp_strjoin(result, "\n", 0);
	}
	fd_putstr(result, output);
	free(result);
}

void	here_doc_file(t_tree *tree, t_env *env, int i)
{
	int	id;
	int	status;
	int	herdoc;

	signal(SIGINT, SIG_IGN);
	id = fork();
	if (id == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		herdoc = open("/tmp/heredoc_", O_CREAT | O_TRUNC | O_RDWR, 0644);
		here_doc(env, herdoc, tree->table->files[i], tree->table->next[i]);
		close(herdoc);
		exit(0);
	}
	free(tree->table->files[i]);
	tree->table->files[i] = ft_strdup("/tmp/heredoc_");
	waitpid(id, &status, 0);
	status += 128;
	g_exit = WEXITSTATUS(status);
	return ;
}

void	get_here_docs(t_tree *tree, t_env *env)
{
	t_tree	*tmp;
	int		i;

	tmp = tree;
	while (tmp->type == 1)
	{
		i = 0;
		while (tmp->left->table->next[i] != 0)
		{
			if (tmp->left->table->next[i] == HERE_DOC
				|| tmp->left->table->next[i] == HERE_DOC_EX)
				here_doc_file(tmp->left, env, i);
			i++;
		}
		tmp = tmp->right;
	}
	i = 0;
	while (tmp->table->next[i] != 0)
	{
		if (tmp->table->next[i] == HERE_DOC
			|| tmp->table->next[i] == HERE_DOC_EX)
			here_doc_file(tmp, env, i);
		i++;
	}
}
