/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 06:17:28 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/08 23:23:25 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	len_s;
	size_t	m;
	size_t	i;

	if (!s)
		return (NULL);
	len_s = ft_strlen(s);
	i = 0;
	if (start >= len_s)
	{
		substring = calloc(sizeof(char), 1);
		return (substring);
	}
	if (len < len_s)
		m = len;
	else
		m = len_s;
	if (!s[0])
		return (NULL);
	substring = calloc(sizeof(char) , (m + 2));
	if (!substring)
		return (NULL);
	while (i < m && start <= len_s)
		substring[i++] = s[start++];
	substring[i] = '\0';
	return (substring);
}
