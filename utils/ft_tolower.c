/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/14 16:03:18 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/19 16:50:28 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h" 

char	*ft_tolower(char *str)
{
	char	*result;
	int		i;

	i = 0;
	result = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			result[i] = str[i] + 32;
		else
			result[i] = str[i];
		i++;
	}
	return (result);
}
