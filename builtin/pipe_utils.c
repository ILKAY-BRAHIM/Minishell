/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 18:37:12 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/17 18:38:12 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builting.h"

void	close_parent_pipe(t_pipe *p)
{
	close(p->p_1[0]);
	close(p->p_2[0]);
	close(p->p_1[1]);
	close(p->p_2[1]);
	p->i = 0;
	while (p->i < p->size)
	{
		waitpid(p->id[p->i], &(p->status), 0);
		p->i++;
	}
}

void	close_open_pipe(t_pipe *p)
{
	if (p->i == 0)
		pipe(p->p_2);
	else if (p->i % 2 != 0)
	{
		close(p->p_1[0]);
		close(p->p_1[1]);
		pipe(p->p_1);
	}
	else if (p->i % 2 == 0)
	{
		close(p->p_2[0]);
		close(p->p_2[1]);
		pipe(p->p_2);
	}
	p->i++;
}
