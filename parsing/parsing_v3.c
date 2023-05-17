/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_v3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:02:43 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/17 17:58:22 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/utils.h"
#include <string.h>
#include <stdio.h>

void	her_doc(char *line, int i)
{
	while (line[++i])
	{
		if (line[i] == '<' && line[i + 1] == '<')
		{
			i = i + 2;
			while (line[i] == ' ' )
				i++;
			while (line[i] && line[i] != ' ')
			{
				(line[i] == '$') && (line[i] = '\5');
				if ((line[i] == '\"' || line[i] == '\'') && i++)
				{
					while (line[i] && !(line[i] == '\"' || line[i] == '\''))
					{
						(line[i] == '$') && (line[i] = '\5');
						i++;
					}
					(line[i] == '\"' || line[i] == '\'') && (i++);
				}
				else
					i++;
			}
			break ;
		}
	}
}

int	free_strlen(char *str)
{
	int	i;

	i = strlen(str);
	free(str);
	return (i);
}

void	tokens_of_qutes(char *line, t_token **token, char *part, int count)
{
	int	i;

	while (line[0])
	{
		i = 0;
		if (line[0] == '\"' || line[0] == '\'')
		{
			part = get_part(line, line[0], line[0], 0);
			if (count == 1 && count++)
				*token = new_token(part);
			else
				lst_add_back(*token, new_token(part));
		}
		else
		{
			while (line[i] && (line[i] != '\"' && line[i] != '\''))
				i++;
			part = get_part(line, line[0], line[i], 2);
			if (count == 1 && count++)
				*token = new_token(part);
			else
				lst_add_back(*token, new_token(part));
		}
		line = line + free_strlen(part);
	}
}

void	rm_dollar(char *line, t_token **token)
{
	int		i;
	char	_p;

	i = 0;
	while (line[i])
	{
		if (line[i] && (line[i] == '\"' || line[i] == '\''))
		{
			_p = line[i];
			i++;
			while (line[i] && line[i] != _p)
				i++;
		}
		if (line[i] == '$' && (line[i + 1] == '\"' || line[i + 1] == '\''))
			line[i] = '\7';
		i++;
	}
	her_doc(line, -1);
	tokens_of_qutes(line, token, NULL, 1);
}

t_token	*_norm_7(t_token *token, t_env *env, t_token *new, int type)
{
	if (type == 1)
		free_lst(new);
	free_lst(token);
	exit_status = 258;
	new_env_var(&env, ft_strjoin("?=", ft_itoa(exit_status)), 2);
	return (NULL);
}

t_token	*_norm_8(t_token *token, t_env *env, t_token *new)
{
	free_lst(token);
	new = join_tokens(new, NULL, 1, NULL);
	if (check_sp(new, 0, NULL, NULL) == -1)
	{
		free_lst(new);
		exit_status = 2;
		new_env_var(&env, ft_strjoin("?=", ft_itoa(exit_status)), 2);
		return (NULL);
	}
	new = join_tokens2(new, 1);
	return (new);
}

t_token	*parsing_v3(char *line, t_env *env, int count)
{
	t_token	*token;
	t_token	*new;
	t_token	*tmp;
	t_token	*tmp_frr;

	rm_dollar(line, &token);
	tmp = token;
	while (tmp != NULL)
	{
		if (count == 1 && count++)
		{
			new = check_token(tmp->token, env, 0, 1);
			if (new == NULL)
				return (_norm_7(token, env, new, 0));
		}
		else
		{
			tmp_frr = check_token(tmp->token, env, 0, 1);
			if (tmp_frr == NULL)
				return (_norm_7(token, env, new, 1));
			lst_add_back(new, tmp_frr);
		}
		tmp = tmp->next;
	}
	return (_norm_8(token, env, new));
}
