/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:39:48 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/08 23:53:13 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_table *saver(char *data)
{
	t_table *table;
	int		i;
	char	index = 1;
	int 	_char;
	char	**array;
	char	**tokons;
	if (data == NULL)
		return (NULL);
	table = calloc(1, sizeof(t_table));
	tokons = calloc(4, sizeof(char *));
	i = 0;
	while(i < 4)
		tokons[i++] = calloc(1, 1);
	i = 0;
	while(data[i])
	{
		while(data[i] && !(data[i] == '\"' || data[i] == '\''))
			i++;
		_char = data[i];
		if (data[i] == _char && index == 1)
			index = -1;
		i++;
		while(data[i] && data[i] != _char  && index == -1)
		{
			if (data[i] == ' ' && index == -1)
				data[i] = '\2';
			i++;
		}
		if (data[i] == _char && index == -1)
			index = 1;
		i++;
	}
	array = ft_split(data, ' ');
	index = 1;
	i = 0;
	while(array[i])
	{
		if (strchr("<>", array[i][0]) )
		{
			tokons[0] = sp_strjoin(tokons[0], array[i], 0);
			tokons[0] = sp_strjoin(tokons[0], strdup(" "),  2);
			
			// rediraction = array[i];
			// file = array[i]
			// if (ft_strncmp("<<", array[i], -1) != 0)
			// {
				i++;
				tokons[1] = sp_strjoin(tokons[1], array[i], 0);
				tokons[1] = sp_strjoin(tokons[1], strdup(" "), 2);
			// }
			// else 
			// {
			// 	i++;
			// 	tokons[3] = sp_strjoin(tokons[3], array[i], 0);
			// 	tokons[3] = sp_strjoin(tokons[3], strdup(" "), 2);
			// }
		}
		else if (index == 1 && index++)
		{
			table->commend = strdup(array[i]);
			// commend = array[i];
			// x = 2;
		}
		else if (array[i][0] == '-' ||(( array[i][0] == '\"' || array[i][0] == '\'') && array[i][1] == '-'))
		{
			tokons[2] = sp_strjoin(tokons[2], array[i], 0);
			tokons[2] = sp_strjoin(tokons[2], strdup(" "), 2);
			// option = array[i];
		}
		else
		{
			tokons[3] = sp_strjoin(tokons[3], array[i], 0);
			tokons[3] = sp_strjoin(tokons[3], strdup(" "), 2);
			// arg = array[i];
		}
		i++;
	}
	free_array(array);
	i = 0;
	array = ft_split(tokons[0], ' ');
	table->arg = ft_split(tokons[3], ' ');
	table->option = ft_split(tokons[2], ' ');
	table->files = ft_split(tokons[1], ' ');
	while(array[i])
		i++;
	// free_array(tokons);
	table->next = calloc(i + 1, sizeof(int));
	i = 0;
	while(array[i])
	{
		if (ft_strncmp(array[i],  ">", -1) == 0)
			table->next[i] = 3;
		else if (ft_strncmp(array[i],  "<", -1) == 0)
			table->next[i] = 2;
		else if (ft_strncmp(array[i],  ">>", -1) == 0)
			table->next[i] = 5;
		else if (ft_strncmp(array[i],  "<<", -1) == 0)
			table->next[i] = 1;
		i++;
	}
	free_array(array);
	// back_space(table);
	return (back_space(table));
}

t_tree *lexer(t_token *lst)
{
	t_token *tmp;
	t_tree	*tree;
	t_tree	*tree_tmp;
	int		count;

	count = 0;
	tmp = lst;
	while(1)
	{
		count++;
		tmp = tmp->next;
		if (tmp == NULL)
			break;
	}
	tree = calloc(1, sizeof(t_tree));
	tree_tmp = tree;
	while(count > 1)
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
	free_lst(lst);
	return (tree_tmp);
}

