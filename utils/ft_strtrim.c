/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 15:40:57 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/19 16:50:28 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strtrim(char *s1, char *set)
{
	size_t	start;
	char	*result;
	int		len;

	len = 0;
	if (!s1 || (s1[0] == '\0' && !set))
		return (NULL);
	start = 0;
	if (*s1)
		len = ft_strlen(s1) - 1;
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (ft_strchr(set, s1[len]) && len)
		len--;
	result = ft_substr(s1, start, (len - start + 1));
	free(s1);
	return (result);
}
