/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_v3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:02:43 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/15 22:56:28 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../utils/utils.h"
#include <string.h>
#include <stdio.h>
void her_doc(char *line)
{
	int i;
	
	i = 0;
	while(line[i])
	{
		if (line[i] == '<' && line[i+1] == '<')
		{
			i = i + 2;
			while (line[i] == ' ' )
				i++;
			while(line[i] && line[i] != ' ')
			{
				if (line[i] == '$')
					line[i] = '\5';
				if (line[i] == '\"' || line[i] == '\'')
				{
					i++;
					while(line[i] && !(line[i] == '\"' || line[i] == '\''))
					{
						if (line[i] == '$')
							line[i] = '\5';
						i++;
					}
					if (line[i] == '\"' || line[i] == '\'')
						i++;
				}
				else 
					i++;
			}
			break ;	
		}
		i++;
	}
}
void rm_dollar(char *line)
{
	int i;

	i = 0;
	while(line[i])
	{
		if (line[i] && (line[i] == '\"' || line[i] == '\''))
		{
			char _p = line[i];
			i++;
			while(line[i] && line[i] != _p)
				i++;
		}
		if (line[i] == '$' && (line[i + 1] == '\"' || line[i + 1] == '\''))
			line[i] = '\7';
		i++;
	}
}
t_token *parsing_v3(char *line, t_env *env)
{
	int i;
	t_token *token;
	t_token *new;
	t_token *tmp;
	char *part;
	int count;

	i = 0;
	while(line[i])
	{
		if (line[i] == '\t')
			line[i] = ' ';
		i++;
	}
	rm_dollar(line);
	count = 1;
	i = 0;
	her_doc(line);
	while(line[i])
	{
		if (line[0] == '\"' || line[0] == '\'')
		{
			part = get_part(line, line[0], line[0], 0);
			if (count == 1)
				token = new_token(part);
			else 
				lst_add_back(token, new_token(part));
		}
		else 
		{
			while(line[i] && (line[i] != '\"' && line[i] != '\''))
				i++;
			part = get_part(line, line[0], line[i], 2);
			if (count == 1)
				token = new_token(part);
			else 
				lst_add_back(token, new_token(part));
		}
		line = line + strlen(part);
		free(part);
		count++;
		i = 0;
	} 
	count = 1;
	tmp = token;

	t_token *tmp_frr;
	while(1)
	{
		if(count == 1)
		{
			new = check_token(tmp->token, env);
			if (new == NULL)
			{
				free_lst(token);
				exit_status = 258;
				new_env_var(&env, ft_strjoin("?=", ft_itoa(exit_status)), 2);
				return(NULL);	
			}
		}
		else 
		{
			tmp_frr = check_token(tmp->token, env);
			if (tmp_frr == NULL)
			{
				free_lst(token);
				exit_status = 127;
				free_lst(new);
				exit_status = 258;
				new_env_var(&env, ft_strjoin("?=", ft_itoa(exit_status)), 2);
				return (NULL);
			}
			lst_add_back(new, tmp_frr);
		}
	 	tmp = tmp->next;
		if (tmp == NULL)
			break;

		count++;
	}
	free_lst(token);
	new = join_tokens(new);
	if (check_sp(new) == -1)
	{
		free_lst(new);
		exit_status = 2;
		new_env_var(&env, ft_strjoin("?=", ft_itoa(exit_status)), 2);
		return (NULL);
	}
	new = join_tokens2(new);
	return (new);
}