/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:49:19 by rrasezin          #+#    #+#             */
/*   Updated: 2023/04/07 05:56:48 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strdup(char *s1)
{
	char	*ret;
	size_t	i;
	size_t	j;

	
	i = ft_strlen(s1) + 1;
	j = 0;
	ret = malloc(i);
	if (!ret)
		return (NULL);
	while (s1[j] != '\0')
	{
		ret[j] = s1[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}
