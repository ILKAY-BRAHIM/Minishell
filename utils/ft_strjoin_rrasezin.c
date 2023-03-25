/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_rrasezin.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 08:00:54 by rrasezin          #+#    #+#             */
/*   Updated: 2023/03/25 08:04:16 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strjoin_rr(char *s1, char *s2)
{
	char	*new;
	size_t	size;
	size_t	j;

	j = 0;
	size = 0;
	if (!s1)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2);
	if (s1 || s2)
		size = size + 2;
	new = ft_calloc(sizeof(char), size);
	if (!new)
		return (NULL);
	size = 0;
	while (s1[size] != '\0')
	{
		new[size] = s1[size];
		size++;
	}
	new[size++] = ' ';
	while (s2[j] != '\0')
		new[size++] = s2[j++];
	free (s1);
	return (new);
}