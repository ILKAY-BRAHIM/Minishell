/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:34:56 by rrasezin          #+#    #+#             */
/*   Updated: 2023/03/25 09:37:39 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_strcmp(char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0' && s2[j] != '\0' && (s1[i] == s2[j]))
	{
		i++;
		j++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[j]);
}
