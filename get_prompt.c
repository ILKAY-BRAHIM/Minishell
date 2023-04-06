/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 01:46:38 by bchifour          #+#    #+#             */
/*   Updated: 2023/04/06 01:42:27 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *get_prompt(void)
{
	char *line;
	line = readline("\033[1;35m minishell ~ \033[0;37m");
	return (line);
}