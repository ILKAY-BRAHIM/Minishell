/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 02:32:05 by bchifour          #+#    #+#             */
/*   Updated: 2023/04/07 18:00:52 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PIPE 1
# define R_INPUT 2
# define R_OUTPUT 3
# define HERE_DOC 4
# define O_APPEND 5
# define SYN_ERR 6

# include <stdio.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "utils/utils.h"

typedef struct s_var
{
	char **split;
	char **tokens;
	int *array;
}			t_var;

typedef struct s_table
{
	char *commend;
	char *arg;
	char *option;
	int	 next;
	char *i_file;
	char *o_file;
	char *e_file;
	char *stop;
} 			t_table;

t_table	*lexer(char *line);
char	*get_prompt(void);
int		cont_sp(char *line);
t_table	*parsing(char *line);
void	execution(t_table *table, t_env *env);
t_env	*new_list(char *org_env);
void	add_back(t_env **list, t_env *new);
void	free_one_list(t_env *list);
void	free_env(t_env *env);
t_env	*init_env(char **org_env);
char	*search_and_return(t_env *env, char *env_var);
void	rm_env_var(t_env *env, char *env_var);
void	new_env_var(t_env *env, char *env_var);
void	ft_echo(t_table *table, int i);
void	ft_env(t_table *table, t_env *env, int i);
void	print_help(t_table *table, int i);

#endif