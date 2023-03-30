/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 07:06:01 by rrasezin          #+#    #+#             */
/*   Updated: 2023/03/30 06:19:46 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../utils/utils.h"

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}			t_env;





static	int env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

char	**get_env(char **env, char *new)
{
	char	**new_env;
	int		nb_env;
	int		i;
	int		j;
	int		add;

	i = 0;
	j = 0;
	add = 0;
	nb_env = env_size(env);
	if (new != NULL)
		add = 1;
	new_env = ft_calloc(nb_env + 1 + add, sizeof(char *));
	while (i < nb_env) // ft_strdup
	{
		new_env[i] = ft_calloc(ft_strlen(env[i]) + 1, sizeof(char));
		while (env[i][j])
		{
			new_env[i][j] = env[i][j];
			j++;
		}
		j = 0;
		i++;
	}
	if (new != NULL) // ft_strdup
	{
		new_env[i] = ft_calloc(ft_strlen(new) + 1, sizeof(char));
		while (new[j])
		{
			new_env[i][j] = new[j];
			j++;
		}
	}
	return (new_env);
}

// char	**change_env_var(char **env, char *new_env)
// {
// 	;
// }

// char	**add_env_var(char **env, char *new_env)
// {
// 	;
// }

int main(int argc, char **argv, char **env)
{
	(void)argc;
	(void)argv;
	int i;
	i = 0;
	
	char **_env = get_env(env, NULL);
	while(_env[i])
	{
		printf ("%s\n", _env[i]);
		i++;
	}
}