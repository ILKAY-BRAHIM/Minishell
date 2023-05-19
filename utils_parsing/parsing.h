/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/18 20:29:22 by bchifour          #+#    #+#             */
/*   Updated: 2023/05/19 16:50:28 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"

void	back_origin(char *str);
int		flaying_qutes_n(char *str, int i, char c);
void	flaying_qutes(char *str);
void	save_qutes(char *str, int start, char __char);
void	flay_gard(char *data, int i, int index, char _char);
void	gards(char **str);
void	norm_1(char **array, char **tokons, int *i);
void	save_tkones(char **str, char **tokons, int y, int *_char);
void	save_tkones_1(char **str, char **tokons, int u, int *_char);
void	norm_(char *str, char **tokons, int *_char);
int		free_ft_strlen(char *str);
void	her_doc(char *line, int i);
int		rp_tab(char **line);
#endif