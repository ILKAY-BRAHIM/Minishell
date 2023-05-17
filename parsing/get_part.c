/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_part.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:42:42 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/16 22:32:44 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//flag = 0  ---> get part include first and end
//flag = 1  ---> get part include first and all of end
//flag = 2  ---> get part include first and nn include end
//flag = 3  ---> get part nn include first and nn include end
//flag = 4  ---> get part nn include first and include end
//flag = 5  ---> get part nn include first and include all of end
char	*reserve(char *str, char *array, char first, char end)
{
	int	i;

	i = 0;
	str = strchr(str, first);
	if (str == NULL)
		return (NULL);
	(first == end) && (i++);
	while (str[i] && str[i] != end)
		i++;
	while (str[i] && str[i] == end)
		i++;
	array = calloc(i + 1, 1);
	return (array);
}

char	*get_part(char *str, char first, char end, int flag)
{
	char				*array;
	unsigned long		i;
	int					j;

	array = NULL;
	if (str == NULL)
		return (NULL);
	array = reserve(str, array, first, end);
	i = 0;
	j = 0;
	(first == end && flag == 1 && str[0] != str[1]) && (array[0] = str[0]);
	if (first == end && flag == 1 && str[0] != str[1])
		return (array);
	if (flag < 3)
		array[j++] = str[i++];
	else
		i++;
	while (str[i] && str[i] != end)
		array[j++] = str[i++];
	if (str[i] && (flag == 2 || flag == 3))
		return (array);
	(str[i] && (flag == 0 || flag == 4)) && (array[j++] = str[i++]);
	while (str[i] && str[i] == end && (flag == 5 || flag == 1))
		array[j++] = str[i++];
	return (array);
}
