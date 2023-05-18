/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 06:17:28 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/18 22:46:16 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "utils.h"

int	size_of_alc(int len_s, int len)
{
	if (len < len_s)
		return (len);
	else
		return (len_s);
}

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
		substring = ft_calloc(sizeof(char), 1);
		return (substring);
	}
	m = size_of_alc(len_s, len);
	if (!s[0])
		return (NULL);
	substring = ft_calloc(sizeof(char), (m + 2));
	if (!substring)
		return (NULL);
	while (i < m && start <= len_s)
		substring[i++] = s[start++];
	substring[i] = '\0';
	return (substring);
}
