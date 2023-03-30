/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 08:14:36 by rrasezin          #+#    #+#             */
/*   Updated: 2023/03/25 08:17:41 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	ft_bzero(void *src, size_t len)
{
	unsigned char	*dest;

	dest = (unsigned char *)src;
	while (len)
	{
		*dest = 0;
		dest++;
		len--;
	}
}
