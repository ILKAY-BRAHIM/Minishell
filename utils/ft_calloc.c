/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 08:14:44 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/19 16:44:53 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*retval;
	size_t	t;

	t = count * size;
	retval = malloc(t);
	if (!retval)
		return (NULL);
	ft_bzero(retval, t);
	return (retval);
}
