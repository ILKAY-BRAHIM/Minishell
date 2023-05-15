/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 21:35:12 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/15 17:08:17 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strnchr(char *s, char first, char end, int flag)
{
	int i;
	int j;
	int size;
	char *array;

	i = 0;
	j = 0;
	size = 0;
	s = strchr(s, first);
	if (s == NULL)
		return (NULL);
	while(s[size] && s[size] != end)
		size++;
	while(s[size] && s[size] == end)
		size++;
	array = ft_calloc(size + 1, 1);
	while(s[i])
	{
		if(s[i] == first)
		{
			array[j++] = s[i++];
			if (flag == 3 && (first == end || first != end))
			{
				while(s[i] && s[i] != end && first != end)
					array[j++] = s[i++];
				while(s[i] && first == end && s[i] == end)
					array[j++] = s[i++];
				return(array);
			}

			while(s[i] && s[i] != end)
				array[j++] = s[i++];
			if (s[i] && (first == end && flag <= 1)) // dyall expand | include first and end in part
			{
				array[j++] = s[i++];
				while(s[i] && (s[i] == end && flag == 1)) // include all of char if = end 
					array[j++] = s[i++];
			}
			else if (s[i] && flag == 2 && (first == end || flag <= 2)) // dyall op
			{
				array[j++] = s[i++];
				while(s[i] && (s[i] == end && flag == 2))
					array[j++] = s[i++];
			}
			return(array);
		}
		i++;
	}
	free(array);
	return (NULL);
}