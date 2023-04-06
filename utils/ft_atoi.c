/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 13:13:11 by rrasezin          #+#    #+#             */
/*   Updated: 2023/04/06 01:03:41 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

int	ft_atoi(const char *str)
{
	long	result;
	int		negative;

	negative = 1;
	result = 0;
	while (*str == 32 || (*str >= 9 && *str <= 13))
	{
		str++;
	}
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			negative = negative * -1;
		str++;
	}
	if (ft_isdigit(*str) == 1)
	{
		while (ft_isdigit(*str) == 1)
		{
			result = (result * 10) + (*str - '0');
			str++;
		}	
		return (result * negative);
	}
	return (0);
}
