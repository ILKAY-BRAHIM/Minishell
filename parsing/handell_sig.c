/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handell_sig.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:14:43 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/10 21:43:01 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


void handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
		
}

void handell_sig()
{
	signal(SIGINT, &handler);
	signal(SIGQUIT, &handler);
}