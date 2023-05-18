/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:49:19 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/18 22:33:27 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include <string.h>

char	*ft_strdup(char *s1)
{
	char	*ret;
	size_t	i;
	size_t	j;

	i = ft_strlen(s1);
	i = i + 1;
	j = 0;
	ret = calloc((i + 8), sizeof(char));
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
