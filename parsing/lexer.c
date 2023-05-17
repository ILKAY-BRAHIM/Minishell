/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:39:48 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/17 23:16:47 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	flay_gard(char *data, int i, int index, char _char)
{
	while (data[i])
	{
		while (data[i] && !(data[i] == '\"'
				|| data[i] == '\'' || data[i] == '`'))
			i++;
		_char = data[i];
		if (data[i] == _char && index == 1)
			index = -1;
		if (data[i])
			i++;
		while (data[i] && data[i] != _char && index == -1)
		{
			if (data[i] && data[i] == ' ' && index == -1)
			{
				(_char == '`') && (data[i] = '\4');
				(_char != '`') && (data[i] = '\2');
			}
			i++;
		}
		if (data[i] == _char && index == -1)
			index = 1;
		if (data[i])
			i++;
	}
}

void	gards(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (strchr(str[i], '`'))
		{
			str[i] = sp_strjoin(str[i], "`", 0);
			i++;
			while (str[i] && !(strchr(str[i], '`')))
			{
				str[i] = sp_strjoin("`", str[i], 1);
				str[i] = sp_strjoin(str[i], "`", 0);
				i++;
			}
			str[i] = sp_strjoin("`", str[i], 1);
			i++;
		}
		else if (str[i])
			i++;
	}
}

void	save_tkones(char **str, char **tokons, int y, int *_char)
{
	while (str[y] && str[y][1] == '-' && *_char == 0)
	{
		if (ft_strlen(str[y]) == 2
			&& str[y][0] == '`' && str[y][1] == '`')
			y++;
		else
		{
			tokons[2] = sp_strjoin(tokons[2], str[y], 0);
			tokons[2] = sp_strjoin(tokons[2], strdup(" "), 2);
			y++;
		}
	}
	while (str[y])
	{
		if (ft_strlen(str[y]) == 2
			&& str[y][0] == '`' && str[y][1] == '`')
			y++;
		else
		{
			tokons[3] = sp_strjoin(tokons[3], str[y], 0);
			tokons[3] = sp_strjoin(tokons[3], strdup(" "), 2);
			*_char = 1;
			y++;
		}
	}
}

void	save_tkones_1(char **str, char **tokons, int u, int *_char)
{
	while (str[u] && (str[u][1] == '-'))
	{
		if (ft_strlen(str[u]) == 2
			&& str[u][0] == '`' && str[u][1] == '`')
			u++;
		else
		{
			tokons[2] = sp_strjoin(tokons[2], str[u], 0);
			tokons[2] = sp_strjoin(tokons[2], strdup(" "), 2);
			u++;
		}
	}
	while (str[u])
	{
		if (ft_strlen(str[u]) == 2
			&& str[u][0] == '`' && str[u][1] == '`')
			u++;
		else
		{
			*_char = 1;
			tokons[3] = sp_strjoin(tokons[3], str[u], 0);
			tokons[3] = sp_strjoin(tokons[3], strdup(" "), 2);
			u++;
		}
	}
}

void	norm_(char *str, char **tokons, int *_char)
{
	int		y;
	char	**array;

	y = 0;
	if (strchr(str, '\4'))
	{
		array = ft_split(str, '\4');
		gards(array);
		save_tkones(array, tokons, 0, _char);
		free_array(array);
	}
	else
	{
		*_char = 1;
		tokons[3] = sp_strjoin(tokons[3], str, 0);
		tokons[3] = sp_strjoin(tokons[3], strdup(" "), 2);
	}
}

void	creat_table(char **tokons, char **array, t_table *table, int i)
{
	array = ft_split(tokons[0], ' ');
	table->arg = ft_split(tokons[3], ' ');
	table->option = ft_split(tokons[2], ' ');
	table->files = ft_split(tokons[1], ' ');
	free_array(tokons);
	while (array[i])
		i++;
	table->next = calloc(i + 1, sizeof(int));
	i = 0;
	while (array[i])
	{
		if (ft_strncmp(array[i], ">", -1) == 0)
			table->next[i] = 3;
		else if (ft_strncmp(array[i], "<", -1) == 0)
			table->next[i] = 2;
		else if (ft_strncmp(array[i], ">>", -1) == 0)
			table->next[i] = 5;
		else if (ft_strncmp(array[i], "<<", -1) == 0)
			table->next[i] = 1;
		i++;
	}
	free_array(array);
}

void	norm_1(char **array, char **tokons, int *i)
{
	tokons[0] = sp_strjoin(tokons[0], array[*i], 0);
	tokons[0] = sp_strjoin(tokons[0], strdup(" "), 2);
	(*i)++;
	tokons[1] = sp_strjoin(tokons[1], array[*i], 0);
	tokons[1] = sp_strjoin(tokons[1], strdup(" "), 2);
}

void	norm_2(char **tokons, char *str, int *_char, t_table *table)
{
	char	**array;

	table->commend = strdup(str);
	array = ft_split(table->commend, '\4');
	gards(array);
	free (table->commend);
	table->commend = strdup(array[0]);
	if (array[1])
		save_tkones_1(array, tokons, 0, _char);
	free_array(array);
}

void	norm_3(char **array, char **tokons, t_table *table)
{
	int	i;
	int	index;
	int	_char;

	i = 0;
	index = 1;
	_char = 0;
	while (array[i])
	{
		if (strchr("<>", array[i][0]))
			norm_1(array, tokons, &i);
		else if (index == 1 && index++)
			norm_2(tokons, array[i], &_char, table);
		else if (_char == 0 && (array[i][0] == '-'
			|| ((array[i][0] == '\"'
				|| array[i][0] == '\'') && array[i][1] == '-')))
		{
			tokons[2] = sp_strjoin(tokons[2], array[i], 0);
			tokons[2] = sp_strjoin(tokons[2], strdup(" "), 2);
		}
		else
			norm_(array[i], tokons, &_char);
		i++;
	}
}

t_table	*saver(char *data)
{
	t_table	*table;
	int		i;
	char	**array;
	char	**tokons;

	if (data == NULL)
		return (NULL);
	table = calloc(1, sizeof(t_table));
	tokons = calloc(5, sizeof(char *));
	i = 0;
	while (i < 4)
		tokons[i++] = calloc(1, 1);
	flay_gard(data, 0, 1, 0);
	array = ft_split(data, ' ');
	norm_3(array, tokons, table);
	free_array(array);
	creat_table(tokons, array, table, 0);
	return (back_space(table, -1));
}

t_tree	*lexer(t_token *lst, int count, t_token *tmp)
{
	t_tree	*tree;
	t_tree	*tree_tmp;

	while (tmp != NULL )
	{
		count++;
		tmp = tmp->next;
	}
	tree = calloc(1, sizeof(t_tree));
	tree_tmp = tree;
	while (count > 1)
	{
		tree->type = 1;
		tree->left = calloc(1, sizeof(t_tree));
		tree->left->type = 0;
		tree->left->table = saver(lst->token);
		tree->right = calloc(1, sizeof(t_tree));
		tree = tree->right;
		lst = lst->next;
		lst = lst->next;
		count -= 2;
	}
	tree->table = saver(lst->token);
	tree->type = 0;
	return (tree_tmp);
}
