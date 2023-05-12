/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 14:39:48 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/12 17:29:38 by rrasezin         ###   ########.fr       */
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
	tokons = calloc(5, sizeof(char *));
	i = 0;
	while(i < 4)
		tokons[i++] = calloc(1, 1);
	i = 0;
	while(data[i])
	{
		while(data[i] && !(data[i] == '\"' || data[i] == '\'' || data[i] == '`'))
			i++;
		_char = data[i];
		if (data[i] == _char && index == 1)
			index = -1;
		if (data[i])
			i++;
		while(data[i] && data[i] != _char  && index == -1)
		{
			if (data[i] && data[i] == ' ' && index == -1)
			{
				if (_char == '`')
					data[i] = '*';
				else
					data[i] = '\2';
				
			}
			i++;
		}
		if (data[i] == _char && index == -1)
			index = 1;
		if (data[i])
			i++;
	}
	array = ft_split(data, ' ');
	// i = 0;
	// while(array[i])
	// {
	// 	if (strchr(array[i], '`'))
	// 	{
	// 		array[i] = sp_strjoin(array[i], "`", 0);
	// 		i++;
	// 		while(array[i] && !(strchr(array[i], '`')))
	// 		{
	// 			array[i] = sp_strjoin("`", array[i], 1);
	// 			array[i] = sp_strjoin(array[i], "`", 0);
	// 			i++;
	// 		}
	// 		array[i] = sp_strjoin("`", array[i], 1);
	// 		i++;
	// 	}
	// 	else if (array[i])
	// 		i++;
	// }
	// i = 0;
	// while(array[i])
	// {
	// 	printf("%s\n", array[i]);
	// 	i++;
	// }
	// pause();
	index = 1;
	i = 0;
	_char = 0;
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
			int u = 1;
			table->commend = strdup(array[i]);
			char **www =ft_split(table->commend, '*');
			u = 0;
			while(www[u])
			{
				if (strchr(www[u], '`'))
				{
					www[u] = sp_strjoin(www[u], "`", 0);
					u++;
					while(www[u] && !(strchr(www[u], '`')))
					{
						www[u] = sp_strjoin("`", www[u], 1);
						www[u] = sp_strjoin(www[u], "`", 0);
						u++;
					}
					www[u] = sp_strjoin("`", www[u], 1);
					u++;
				}
				else if (www[u])
					u++;
			}
			u = 1;
			table->commend = strdup(www[0]);

			if (www[u])
			{
				while (www[u] && (www[u][1] == '-'))
				{
					if (ft_strlen(www[u]) == 2 && www[u][0] == '`' && www[u][1] == '`')
						u++;
					else
					{
						tokons[2] = sp_strjoin(tokons[2], www[u], 0);
						tokons[2] = sp_strjoin(tokons[2], strdup(" "), 2);
						u++;
					}
				}
				while(www[u])
				{
					if (ft_strlen(www[u]) == 2 && www[u][0] == '`' && www[u][1] == '`')
						u++;
					else
					{
						_char = 1;
						tokons[3] = sp_strjoin(tokons[3], www[u], 0);
						tokons[3] = sp_strjoin(tokons[3], strdup(" "), 2);
						u++;
					}
				}
			}
			
			// commend = array[i];
			// x = 2;
		}
		else if (_char == 0 && (array[i][0] == '-' ||(( array[i][0] == '\"' || array[i][0] == '\'') && array[i][1] == '-')))
		{
			tokons[2] = sp_strjoin(tokons[2], array[i], 0);
			tokons[2] = sp_strjoin(tokons[2], strdup(" "), 2);
			// option = array[i];
		}
		else
		{
			if (strchr(array[i], '*'))
			{
				int y = 0;
				char **tfo = ft_split(array[i], '*');

				while(tfo[y])
				{
					if (strchr(tfo[y], '`'))
					{
						tfo[y] = sp_strjoin(tfo[y], "`", 0);
						y++;
						while(tfo[y] && !(strchr(tfo[y], '`')))
						{
							tfo[y] = sp_strjoin("`", tfo[y], 1);
							tfo[y] = sp_strjoin(tfo[y], "`", 0);
							y++;
						}
						tfo[y] = sp_strjoin("`", tfo[y], 1);
						y++;
					}
					else if (tfo[y])
						y++;
				}
				y = 0;
				while(tfo[y] && tfo[y][1] == '-' && _char == 0)
				{
					if (ft_strlen(tfo[y]) == 2 && tfo[y][0] == '`' && tfo[y][1] == '`')
						y++;
					else
					{
						tokons[2] = sp_strjoin(tokons[2], tfo[y], 0);
						tokons[2] = sp_strjoin(tokons[2], strdup(" "), 2);
						y++;
					}
				}
				while(tfo[y])
				{
					if (ft_strlen(tfo[y]) == 2 && tfo[y][0] == '`' && tfo[y][1] == '`')
						y++;
					else
					{
						tokons[3] = sp_strjoin(tokons[3], tfo[y], 0);
						tokons[3] = sp_strjoin(tokons[3], strdup(" "), 2);
						_char = 1;
						y++;
					}
				}
			}
			else
			{
				_char = 1;
				tokons[3] = sp_strjoin(tokons[3], array[i], 0);
				tokons[3] = sp_strjoin(tokons[3], strdup(" "), 2);
			}
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
	free_array(tokons);
	while(array[i])
		i++;
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
	// free_lst(lst);
	return (tree_tmp);
}

