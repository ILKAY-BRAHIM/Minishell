/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 06:17:28 by rrasezin          #+#    #+#             */
/*   Updated: 2023/03/25 06:17:30 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
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
	if (len < len_s)
		m = len;
	else
		m = len_s;
	substring = malloc(sizeof(char) * (m + 1));
	if (!substring || !s[0])
		return (NULL);
	while (i < m && start <= len_s)
		substring[i++] = s[start++];
	substring[i] = '\0';
	return (substring);
}
