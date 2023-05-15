/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:59:06 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/16 00:55:14 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token	*_print_r(void)
{
	write(2, "minishell: unexpected EOF ", 26);
	write(2, "while looking for matching\n", 27);
	return (NULL);
}

t_token	*qutes(char *data, t_env *env)
{
	t_token	*new;

	if (data[0] == '\"')
	{
		if (data[ft_strlen(data) - 1] == '\"' && data[1] != '\0')
		{
			if (strchr(data, '$'))
				data = expanding(data, env);
			new = new_token(data);
		}
		else
			return (_print_r());
	}
	else if (data[0] == '\'')
	{
		if (data[ft_strlen(data) - 1] != '\'' || data[1] == '\0')
			return (_print_r());
		else
			new = new_token(data);
	}
	return (new);
}

t_token	*check_token(char *data, t_env *env)
{
	char	**split;
	char	*part;
	int		count;
	char	*str;
	char	fin;
	int		x;
	int		i;
	t_token *new;

	i = 0;
	count = 1;
	if (data[0] == '\"' || data[0] == '\'')
		new = qutes(data, env);
	else
	{
		split = ft_strtok(data, "<>|", 1);
		i = 0;
		while (split[i])
		{
			fin = split[i][strlen(split[i]) - 1];
			x = 0;
			if (split[i][0] != fin && (fin == '|' || fin == '>' || fin == '<'))
			{
				part = get_part(split[i], split[i][0], fin, 2);
				while (part[x] && part[x] == ' ')
					x++;
				if (part[x] != '\0')
				{
					if (strchr(part, '$'))
						part = expanding(part, env);
					if (count == 1 && count++)
						new = new_token(part);
					else
						lst_add_back(new, new_token(part));
				}
				free(part);
				str = strchr(split[i], fin);
				if (count == 1 && count++)
					new = new_token(str);
				else
					lst_add_back(new, new_token(str));
			}
			else
			{
				if (strchr(split[i], '$'))
				{
					part = expanding(split[i], env);
					if (count == 1 && count++)
						new = new_token(part);
					else
						lst_add_back(new, new_token(part));
					free(part);
				}
				else
				{
					if (count == 1 && count++)
						new = new_token(split[i]);
					else
						lst_add_back(new, new_token(split[i]));
				}
			}
			i++;
		}
		free_array(split);
	}
	return (new);
}