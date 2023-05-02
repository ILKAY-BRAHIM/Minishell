/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 18:47:47 by bchifour          #+#    #+#             */
/*   Updated: 2023/04/18 21:50:53 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <string.h>

char	*ft_strnchr(char *s, char first, char end, int count)
{
	size_t	i;
	int j;
	int		size;
	char	*array;

	i = 0;
	j = 0;
	size = 0;
	array = strchr(s, first);
	// while(count-- > 1)
	// {
	// 	printf("kkkkkk\n");
	// 	array = strchr(array+1, first);
	// }
	if (array == NULL)
		return(NULL);
	s = strdup(array);
	i = 0;
	while(array[size] && array[size] != end)
		size++;
	while(array[size] && array[size] == end)
		size++;
	array = calloc(size+1, 1);
	while(s[i])
	{
		if(s[i] == first )
		{
			array[j++] = s[i++];
			while(s[i] && s[i] != end)
				array[j++] = s[i++];
			if (s[i] && (first == end && count <= 1)) // dyall expand
			{
				array[j++] = s[i++];
				while(s[i] && (s[i] == end && count == 1))
					array[j++] = s[i++];
			}
			else if (s[i] && count == 2 && (first == end || count <= 2)) // dyall op
			{
				array[j++] = s[i++];
				while(s[i] && (s[i] == end && count == 2))
					array[j++] = s[i++];
			}
			free(s);
			return (array);
		}
		i++;
	}
	free(array);
	free(s);
	return (NULL);
}
