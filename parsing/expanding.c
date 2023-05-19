/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:20:59 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/19 16:51:13 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	_norm_5(char *str, char **new, t_env *env, char *array)
{
	int	i;

	i = 1;
	while (str[i] && (isdigit(str[i]) || isalpha(str[i])
			|| str[i] == '_' || str[i] == '?' || str[i] == '@'))
		i++;
	if (str[i] == '$')
		array = get_part(str, '$', str[i], 2);
	else
		array = get_part(str, '$', str[i], 2);
	ft_memmove(str, (str) + ft_strlen(array), ft_strlen((str) + ft_strlen(array)) + 1);
	if (*((array) + 1) == '?')
	{
		*new = search_and_return (env, "?", 1);
		*new = sp_strjoin(*new, (array) + 2, 0);
	}
	else if ((*((array) + 1) >= '0'
			&& *((array) + 1) <= '9') || *((array) + 1) == '@')
		*new = ft_strdup((array) + 2);
	else
		*new = search_and_return (env, (array) + 1, 1);
	free (array);
}

void	_norm_6(char **array, char **new, int i)
{
	if (*array == NULL || (*array)[0] == 0)
		*array = ft_strdup("\7");
	else
	{
		i = 0;
		while ((*array)[i])
		{
			if ((*array)[i] == '\t')
				(*array)[i] = ' ';
			i++;
		}
		i = 0;
		*new = ft_strdup("`");
		*array = sp_strjoin(*new, *array, 2);
		*array = sp_strjoin(*array, ft_strdup("`"), 2);
	}
}

char	*expand(char *str, t_env *env)
{
	char	*array;
	char	*new;

	array = ft_strchr(str, '$');
	if (ft_strlen(str) <= 1 || str[1] == ' ' || str[1] == '\"' || (!isalpha(str[1])
			&& !isdigit(str[1]) && str[1] != '_'
			&& str[1] != '?' && str[1] != '@'))
		return (str);
	if (array != NULL)
	{
		array = ft_strchr(str + 1, '$');
		if (array != NULL)
			return (str);
		_norm_5(str, &new, env, array);
		array = new;
		_norm_6(&array, &new, 0);
	}
	if (array != NULL)
	{
		new = ft_strdup(str);
		free (str);
		str = sp_strjoin(array, new, 2);
	}
	return (str);
}

char	*norm_4(t_env *env, char *begin, char *str)
{
	char	**array;
	char	*result;
	int		i;

	i = 0;
	result = ft_calloc(1, 1);
	array = ft_strtok(str, "$", 2);
	if (begin != NULL)
		begin = expand(begin, env);
	i = 0;
	while (array[i])
	{
		array[i] = expand(array[i], env);
		i++;
	}
	if (begin != NULL)
		result = sp_strjoin(result, begin, 2);
	else
		free(begin);
	i = 0;
	while (array[i])
		result = sp_strjoin(result, array[i++], 0);
	free_array(array);
	return (result);
}

char	*expanding(char *str, t_env *env)
{
	char	*begin;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!(ft_strchr(str, '$')))
		return (str);
	begin = NULL;
	while (1)
		if (str[++i] == '$' && str[i + 1] != '$')
			break ;
	if (i != 0)
	{
		begin = ft_calloc(i + 1, 1);
		while (++j < i)
			begin[j] = str[j];
		ft_memmove(str, str + i, ft_strlen(str + i) + 1);
	}
	return (norm_4(env, begin, str));
}
