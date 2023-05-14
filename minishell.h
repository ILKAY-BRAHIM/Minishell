/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 22:38:48 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/14 22:24:04 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
// # include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <string.h>
# include "utils/utils.h"
#include <ctype.h>

# define HERE_DOC_EX 1
# define R_INPUT 2
# define R_OUTPUT 3
# define HERE_DOC 4
# define R_APPEND 5

int	exit_status;


typedef struct s_token
{
	char	*token;
	char	*sp;
	int		id;
	struct s_token *next;
	
} 			t_token;

typedef struct s_table
{
	char	*commend;
	char	**arg;
	int		*exp;
	char	**option;
	int		*next;
	char	**files;
} 			t_table;

typedef struct s_tree
{
	int type;
	t_table *table;
	struct s_tree *left;
	struct s_tree *right;
}				t_tree;

// void rl_replace_line(const char *str, int i);
// int rl_on_new_line();
t_token	*new_token(char *data);
void lst_add_back(t_token *lst, t_token *new);
t_token *parsing_v3(char *line, t_env *env);
char	*ft_strnchr(char *s, char first, char end, int flage);
char	*get_prompt(void);
t_env	*new_list(char *org_env, int type);
void	add_back(t_env **list, t_env *new);
void	free_one_list(t_env *list);
void	free_env(t_env *env);
t_env	*init_env(char **org_env);
char	*search_and_return(t_env *env, char *env_var, int type);
void	rm_env_var(t_env **env, char *env_var);
void	new_env_var(t_env *env, char *env_var, int type);
void	*ft_memmove(void *dst, const void *src, size_t len);
int count_sp(char *line);
t_token *check_token(char *data, t_env *env);
char **ft_strtok(char *str, char *sp, int att);
char	*sp_strjoin(char *s1, char *s2, int att);
char	*expanding(char *str, t_env *env);
void	free_lst(t_token *token);
t_token		*join_tokens(t_token *tokens);
t_token *r_qutes(t_token *tokens);
int		check_sp(t_token *token);
char	*get_part(char *str, char first, char end, int flag);
t_tree *lexer(t_token *lst);
t_token *join_tokens2(t_token *lst);
void	free_array(char **array);
char	*ft_itoa(int n);
t_table *back_space(t_table *table);
// void handell_sig();
void	execution(t_tree *tree, t_env **env);
void	fd_putchar(char c, int fd);
char 	*hanty_7ada_wlat_wa7da_khera(char *str);
// void	execute_commande(t_table *table, t_env *env);

// void	print_help(t_table *table, int i);
#endif