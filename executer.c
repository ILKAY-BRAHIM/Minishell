/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:27:22 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/02 18:07:09 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_commande(t_table *table, t_env *env, int i)
{
	if (ft_strncmp("echo", table[i].commend, -1) == 0)
		ft_echo(table, i);
	else if (ft_strncmp("env", table[i].commend, -1) == 0)
		ft_env(table, env, i);
	// else if (ft_strncmp("export", table[i].commend, -1) == 0)
	// 	ft_export(table, env, i);
	// else if (ft_strncmp("unset", table[i].commend, -1) == 0)
	// 	ft_unset(table, env, i);
	// else if (ft_strncmp("cd", table[i].commend, -1) == 0)
	// 	ft_cd(table, i);
	// else if (ft_strncmp("pwd", table[i].commend, -1) == 0)
	// 	ft_pwd(table, i);
	// else if (ft_strncmp("exit", table[i].commend, -1) == 0)
	// 	ft_exit(table, i);
	// else
	// 	ft_execute(table, env);
	return ;
}

void	execution(t_table *table, t_env *env)
{
	int	i;

	i = 0;
	if (table[i].next == 0)
		simple_commande(table, env, 0);
	// else 
	// {
	// 	while (table[i]->next)
	// 	{
	// 		if (table[i]->next == 1)
	// 			pipex(table, env);
	// 		i++;
	// 	}
	// }
	return ;
}