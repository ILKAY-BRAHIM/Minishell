/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 22:59:06 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/02 18:06:49 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_token *check_token(char *data, t_env *env)
{
	
	char **split;
	char *part;
	int count;
	char *str;
	char fin;
	int x;
	int i;
	i = 0;
	count = 1;
	t_token *new;
	if(data[0] == '\"')
	{
		if (data[ft_strlen(data)-1] == '\"' && data[1] != '\0')
		{
			if (strchr(data, '$'))
			{
				data = expanding(data, env);
				i = 2;
			}
			new = new_token(data);
			if (i == 2)
			{
				// free(data);
				i = 0;
			}
		}
		else
		{
			printf("minishell: syntax error near unexpected close `\"`\n");
			// free(data);
			return(NULL);
		}
	}
	else if(data[0] == '\'')
	{
		if (data[ft_strlen(data) - 1] != '\'' || data[1] == '\0')
		{
				printf("minishell: syntax error near unexpected close `\'` \n");
				return (NULL);
		}
		else
			new = new_token(data);
		// free(data);
	}
	else
	{

		split = ft_strtok(data, "<>|", 1);
		i = 0;
		while(split[i])
		{
			// if (i == 0)
			// {
			// 	free_lst(new_tokenn);
			// 	// new_tokenn->token = NULL;	
			// }
			fin = split[i][strlen(split[i]) - 1];
			x = 0;
			if (split[i][0] != fin  && (fin == '|' || fin == '>' || fin == '<'))
			{

				part = get_part(split[i], split[i][0], fin, 2);
				while(part[x] && part[x] == ' ')
					x++;
				if (part[x] != '\0')
				{
					if(strchr(part, '$'))
						part = expanding(part, env);
					if (count == 1 && count++)
					{
						new = new_token(part);
						
					}
					else
					{
						lst_add_back(new, new_token(part));
					}
				}
				str = strchr(split[i], fin);
					if (count == 1 && count++)
					{
						new = new_token(str);
					}
					else
					{
						lst_add_back(new, new_token(str));
					}
			}
			else
			{
				part = expanding(split[i], env);
				if (count == 1 && count++)
				{
					new = new_token(part);
				}
				else 
				{
					lst_add_back(new, new_token(part));
				}
			}
			i++;
			
		}
		// i = 0;
		// while(split[i])
		// {
		// 	if(strchr(split[i], '$'))
		// 		split[i] = expanding(split[i], env);
		// 	if (i == 0)
		// 		new_tokenn = new_token(split[i]);
		// 	else
		// 		lst_add_back(new_tokenn, new_token(split[i]));
		// 	i++;
		// }
		i = 0;
		while(split[i])
		{
			free(split[i]);
			i++;
		}
		free(split);
		split = NULL;
		
	}
	// if (c == 2)
	// {
	// 	printf("OK\n");
	// 	while(1)
	// 	{
	// 		printf("********** %s\n", new->token);
	// 		new = new->next;
	// 		if (new == NULL)
	// 			break ;
	// 	}
	// 	pause();
	// }
	return (new);
}