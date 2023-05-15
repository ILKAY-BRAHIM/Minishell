/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 01:35:01 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/14 22:49:19 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"

int	ft_pwd(t_table *table, t_env *env)
{
	char	*cd;

	if (env && search_and_return(env, "_", 0))
		rm_env_var(&env, "_");
	new_env_var(env, ft_strjoin("_=", ft_strdup("pwd")), 0);
	if (table->option[0] != NULL)
	{
		print_help(table, 0);
		return (1);
	}
	else 
	{
		cd = getcwd(NULL, 0);
		if (cd == NULL)
			perror("");
		else
		{
			fd_putstr(cd, 1);
			fd_putchar('\n', 1);
		}
		free(cd);
	}
	return (0);
}