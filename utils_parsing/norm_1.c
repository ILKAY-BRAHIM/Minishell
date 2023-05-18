/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 21:17:57 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/18 21:18:50 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	norm_1(char **array, char **tokons, int *i)
{
	tokons[0] = sp_strjoin(tokons[0], array[*i], 0);
	tokons[0] = sp_strjoin(tokons[0], strdup(" "), 2);
	(*i)++;
	tokons[1] = sp_strjoin(tokons[1], array[*i], 0);
	tokons[1] = sp_strjoin(tokons[1], strdup(" "), 2);
}
