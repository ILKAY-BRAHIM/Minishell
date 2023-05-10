/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 01:35:01 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/10 15:54:52 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "builting.h"

int	ft_pwd(t_table *table, t_env *env)
{
	char	cd[1024];

	rm_env_var(&env, "_");
	new_env_var(env, ft_strjoin("_=", ft_strdup("pwd")), 0);
	if (table->option[0] != NULL)
	{
		print_help(table, 0);
		return (1);
	}
	else 
	{
		if (getcwd(cd, sizeof(cd)) == NULL)
			perror("getcwd() error");
		else
			printf("%s\n", cd);
	}
	return (0);
}