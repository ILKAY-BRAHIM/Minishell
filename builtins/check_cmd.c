/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 09:32:37 by rrasezin          #+#    #+#             */
/*   Updated: 2023/03/25 09:42:02 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/utils.h"

void	check_cmd(t_table *cmd, char **env)
{
	if (ft_strcmp(cmd->commend, "echo") == 0)
		ft_echo(cmd);
	if (ft_strcmp(cmd->commend, "env") == 0)
		get_env(env, NULL);
}