/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 17:33:29 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/02 18:06:49 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

char	*re(int n, int i, char *new)
{
	long	nb;

	i = i - 1;
	if (n < 0)
		new[0] = '-';
	nb = n;
	while (nb)
	{
		if (nb < 0)
			nb = -nb;
		new[i--] = (nb % 10) + '0';
		nb = nb / 10;
	}
	if (n == 0)
	{
		new[i--] = (nb % 10) + '0';
		nb = nb / 10;
	}
	return (new);
}

char	*ft_itoa(int n)
{
	long	i;
	char	*new;
	long	nb;
	char	x;

	x = 0;
	i = 0;
	nb = n;
	while (nb != 0)
	{
		if (nb < 0)
		{
			i = i + 1;
			nb = -nb;
		}
		nb = nb / 10;
		i++;
	}
	if (n == 0)
		i = 1;
	new = (char *)calloc(i + 1, sizeof(char));
	if (!new)
		return (NULL);
	new = re(n, i, new);
	return (new);
}
