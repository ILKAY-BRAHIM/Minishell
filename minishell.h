/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 02:32:05 by bchifour          #+#    #+#             */
/*   Updated: 2023/03/25 03:14:19 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
typedef struct s_table
{
	char *commend;
	char **arg;
	char *next;
	char *i_file;
	char *o_file;
	char *e_file;
	char **env;
} 			t_table;

#endif