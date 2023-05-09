/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:13:24 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/09 15:19:07 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	size_t	i;
	size_t	j;
	size_t	len_s1;
	size_t	len_s2;

	if (!s1 || !s2)
		return (NULL);
	len_s1 = ft_strlen(s1);
	len_s2 = ft_strlen(s2);
	i = 0;
	j = 0;
	new = calloc(sizeof(char) , (len_s1 + len_s2 + 1));
	if (!new)
		return (NULL);
	while (s1[j] != '\0')
		new[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0' && len_s2-- > 0)
		new[i++] = s2[j++];
	new[i] = '\0';
	free(s2);
	return (new);
}
