/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_help.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/07 17:55:16 by rrasezin          #+#    #+#             */
/*   Updated: 2023/04/07 18:29:37 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_help(t_table *table, int i)
{
	if (table[i].option)
	{
		printf("%s: illegal option -- %c\n", table[i].commend, table[i].option[1]);
		printf("usage: %s [no option]\n", table[i].commend);
	}
	return;
}