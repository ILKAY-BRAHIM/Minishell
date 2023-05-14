/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 18:20:59 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/14 14:29:22 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*expand(char *str, t_env *env)
{
	char	*array;
	char	*new;
	int		i;

	array = strchr(str, '$');
	if (strlen(str) <= 1 || str[1] == ' ' || str[1] == '\"' || (!isalpha(str[1]) && !isdigit(str[1]) && str[1] != '_' && str[1] != '?' && str[1] != '@'))
		return (str);
	if (array != NULL)
	{
		array = strchr(str + 1, '$');
		if (array != NULL)
			return (str);
		i = 1;
		while (str[i] && (isdigit(str[i]) || isalpha(str[i]) || str[i] == '_' || str[i] == '?' || str[i] == '@'))
			i++;
		if (str[i] == '$')
			array = get_part(str, '$', str[i], 2);
		else
			array = get_part(str, '$', str[i], 2);
		ft_memmove(str, str + strlen(array), strlen(str + strlen(array)) + 1);
		if (*(array+1) == '?')
		{
			new = search_and_return (env, "?");
			new = sp_strjoin(new, array+2, 0);
		}
		else if((*(array+1) >= '0' && *(array+1) <= '9' )|| *(array+1) == '@')
		{
			// new = search_and_return (env, *(array+1));
			// new = sp_strjoin("", array+2, 0);
			new = strdup(array+2);
		}
		else
			new = search_and_return (env, array + 1);
		free (array);
		array = new;
		if (array == NULL || array[0] == 0)
		{
			// array = sp_strjoin("\6", array, -1);
			// array = sp_strjoin(array, "\6", 0);
			array = strdup("\7");
		}
		else
		{
			i = 0;
			while(array[i])
			{
				if(array[i] == '\t')
					array[i] = ' ';
				i++;
			}
			i = 0;
			new = strdup("`");
			array = sp_strjoin(new, array, 2);
			array = sp_strjoin(array, strdup("`"), 2);
		}
	}
	if (array != NULL)
	{
		new = strdup(str);
		free (str);
		str = sp_strjoin(array, new, 2);
	}
	return (str); 
}
char	*expanding(char *str, t_env *env)
{
	char	**array;
	char	*begin;
	char	*result;
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!(strchr(str, '$')))
		return (str);
	result = ft_calloc(1, 1);
	begin = NULL;
	while (1)
		if (str[++i] == '$' && str[i + 1] != '$')
			break ;
	if (i != 0)
	{
		begin = ft_calloc(i + 1, 1);
		while(++j < i)
			begin[j] = str[j];
		ft_memmove(str, str+i, strlen(str+i) + 1);
	}
	array = ft_strtok(str, "$", 2);
	if (begin != NULL)
		begin = expand(begin, env);
	i = 0;
	while(array[i])
	{
		array[i] = expand(array[i], env);
		i++;
	}
	if (begin != NULL)
		result = sp_strjoin(result, begin, 2);
	else
		free(begin);
	i = 0;
	while(array[i])
		result = sp_strjoin(result, array[i++], 0);
	free_array(array);
	// free(str);
	return (result);
}

// int main(int argc, char **argv, char **old_env)
// {
// 	t_env *env;
// 	char *list;
// 	char *new;
// 	(void)argc;
// 	env = init_env(old_env);
// 	new = strdup(argv[1]);
// 	list = expanding(new, env);
// 	// free(new);
// 	printf("%s\n", list);
// 	pause();
// 	// pause();
// }