/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 02:46:52 by bchifour          #+#    #+#             */
/*   Updated: 2023/04/07 05:33:08 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <string.h>

char	*ft_revstr(char *str, char *first, char *end, int count)
{
	int __i = strlen(first);
	char *array = strnstr(str, first, -1);
	if (array == NULL)
		return (NULL);
	while(--count > 0)
		array = strnstr(array+1, first, -1);
	if (array == NULL)
		return (NULL);
	char *secound = strnstr(array + __i, end, -1);
	int i = ft_strlen(array);
	int _i = ft_strlen(secound);
	int x = i - _i;
	int j = 0;
	char *new = calloc(x + 1, 1);
	while(array[__i] && array[__i] != '$')
	{
		new[j++] = array[__i++];
	}
	return (new);
}
#include <stdio.h>
int main()
{
	char array[90] = "$hfhfg. .     ffffff    fffffff         .$hfhfg dddddddddddd $//////// 666666666666";
	printf("%s\n", ft_revstr(array, "$", "$", 3));
}