/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 02:32:05 by bchifour          #+#    #+#             */
/*   Updated: 2023/03/30 06:45:22 by bchifour         ###   ########.fr       */
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
	char **arg;
	char *option;
	int	 next;
	char *i_file;
	char *o_file;
	char *e_file;
	char **env;
	char *stop;
} 			t_table;

char *get_prompt(void);
void	lexer(char *line);



#endif