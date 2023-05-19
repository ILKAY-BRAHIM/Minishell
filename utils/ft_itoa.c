/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 12:14:22 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/19 16:44:53 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

static	int	int_len(long n)
{
	int	len;

	len = 0;
	if (n <= 0)
	{
		n = n * -1;
		len++;
	}
	while (n > 0)
	{
		n = n / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*result;
	long	i;
	int		m;
	long	k;

	i = int_len(n);
	m = 0;
	k = (long)n;
	result = ft_calloc(i + 1, sizeof(char));
	if (k < 0)
	{
		k = k * -1;
		m = 1;
	}
	if (!result)
		return (NULL);
	while (i - m)
	{
		result[i - 1] = k % 10 + '0';
		k = k / 10;
		i--;
	}
	if (m == 1)
		result[i - 1] = '-';
	return (result);
}
