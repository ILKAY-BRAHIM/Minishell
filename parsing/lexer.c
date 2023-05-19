/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:39:48 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/19 16:51:13 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	creat_table(char **tokons, char **array, t_table *table, int i)
{
	array = ft_split(tokons[0], ' ');
	table->arg = ft_split(tokons[3], ' ');
	table->option = ft_split(tokons[2], ' ');
	table->files = ft_split(tokons[1], ' ');
	free_array(tokons);
	while (array[i])
		i++;
	table->next = ft_calloc(i + 1, sizeof(int));
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

void	norm_2(char **tokons, char *str, int *_char, t_table *table)
{
	char	**array;

	table->commend = ft_strdup(str);
	array = ft_split(table->commend, '\4');
	gards(array);
	free (table->commend);
	table->commend = ft_strdup(array[0]);
	if (array[1])
		save_tkones_1(array, tokons, 1, _char);
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
		if (ft_strchr("<>", array[i][0]))
			norm_1(array, tokons, &i);
		else if (index == 1 && index++)
			norm_2(tokons, array[i], &_char, table);
		else if (_char == 0 && (array[i][0] == '-'
			|| ((array[i][0] == '\"'
				|| array[i][0] == '\'') && array[i][1] == '-')))
		{
			tokons[2] = sp_strjoin(tokons[2], array[i], 0);
			tokons[2] = sp_strjoin(tokons[2], ft_strdup(" "), 2);
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
	table = ft_calloc(1, sizeof(t_table));
	tokons = ft_calloc(5, sizeof(char *));
	i = 0;
	while (i < 4)
		tokons[i++] = ft_calloc(1, 1);
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
	tree = ft_calloc(1, sizeof(t_tree));
	tree_tmp = tree;
	while (count > 1)
	{
		tree->type = 1;
		tree->left = ft_calloc(1, sizeof(t_tree));
		tree->left->type = 0;
		tree->left->table = saver(lst->token);
		tree->right = ft_calloc(1, sizeof(t_tree));
		tree = tree->right;
		lst = lst->next;
		lst = lst->next;
		count -= 2;
	}
	tree->table = saver(lst->token);
	tree->type = 0;
	return (tree_tmp);
}
