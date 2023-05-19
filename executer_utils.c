/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 17:00:47 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/19 17:08:45 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "builtin/builting.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void	red_smp_cmd(t_table *table, t_env **env, int executed)
{
	int	status;

	status = 0;
	// signal(SIGINT, SIG_DFL);
	redirection(table);
	if (executed == 0 && table->commend)
	{
		status = execute_commande(table, env, 1);
		exit(status);
	}
	exit(g_exit);
}

void	ex_here_docs(t_tree *tree, t_env **env)
{
	// signal(SIGINT, SIG_DFL);
	get_here_docs(tree, *env);
	g_exit = pipex(tree, env);
	exit(g_exit);
}
