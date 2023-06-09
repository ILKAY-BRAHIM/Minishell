/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handell_sig.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 19:14:43 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/30 16:02:54 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handler(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handell_sig(void)
{
	signal(SIGINT, &handler);
	signal(SIGQUIT, SIG_IGN);
}
