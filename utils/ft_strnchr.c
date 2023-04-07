/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 15:12:12 by rrasezin          #+#    #+#             */
/*   Updated: 2023/04/07 16:55:39 by bchifour         ###   ########.fr       */
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
	while(count-- > 1)
	{
		array = strchr(array+1, first);
	}
	if (array == NULL)
		return(NULL);
	s = ft_strdup(array);
	i = 0;
	size = ft_strlen(array) - ft_strlen(strchr(array+1, end));
	array = calloc(size+1, 1);
	while(s[i])
	{
		if(s[i] == first )
		{
			i++;
			while(s[i] && s[i] != end)
				array[j++] = s[i++];
			if (s[i] && s[i] == end && s[i] != ' ' && s[i] != '$')
				array[j++] = s[i++];
			free(s);
			return (array);
		}
		i++;
	}
	free(s);
	return (NULL);
}

// #include <stdio.h>
// int main()
// {
// 	char array[100] = "$asasdasdad";
// 	printf("%s\n", ft_strnchr(array, '$', ' ', 1));
// }