/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sp_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/14 19:13:24 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/15 14:36:40 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 0 -> free s1
// 1 -> free s2
// 2 -> free s1 && s2
// outher -> no free

char	*sp_strjoin(char *s1, char *s2, int att)
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
	new = ft_calloc(sizeof(char) , (len_s1 + len_s2 + 2));
	if (!new)
		return (NULL);
	while (s1[j] != '\0')
		new[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0' && len_s2-- > 0)
		new[i++] = s2[j++];
	new[i] = '\0';
	if (att == 2)
	{
		free(s1);
		att--;
		s1 = NULL;
	}
	if (att == 1)
	{
		free(s2);
		s2 = NULL;
	}
	if (att == 0)
		free(s1);
	return (new);
}
