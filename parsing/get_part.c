/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_part.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 23:42:42 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/02 18:06:49 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//flag = 0  ---> get part include first and end
//flag = 1  ---> get part include first and all of end
//flag = 2  ---> get part include first and nn include end
//flag = 3  ---> get part nn include first and nn include end
//flag = 4  ---> get part nn include first and include end
//flag = 5  ---> get part nn include first and include all of end

char	*get_part(char *str, char first, char end, int flag)
{
	char	*array;
	unsigned long		i;
	int		j;

	i = 0;
	str = strchr(str, first);
	if (str == NULL)
		return (NULL);
	if (first == end)
		i++;
	while(str[i] && str[i] != end )
		i++;
	while(str[i] && str[i] == end )
		i++;
	array = calloc(i + 1, 1);
	// if (i == strlen(str) && (str[1] != '<' || str[1] != '>'))
	// {
	// 	array[0] = str[0];
	// 	return (array);
	// }
	i = 0;
	j = 0;
	if (first == end && flag == 1 && str[0] != str[1])
	{
		array[0] = str[0];
		return (array);
	}	
	if (flag < 3)
		array[j++] = str[i++];
	else
		i++;
	while(str[i] && str[i] != end)
		array[j++] = str[i++];
	if (str[i] && (flag == 2 || flag == 3))
		return (array);
	if (str[i] && (flag == 0 || flag == 4))
		array[j++] = str[i++];
	while (str[i] && str[i] == end && (flag == 5 || flag == 1))
		array[j++] = str[i++];
	return (array);
}
// int main ()
// {
// 	char s[50] = "\"hhhhhh\" ls";
// 	printf("%s\n", get_part(s, '\"', '\"', 0));
// }