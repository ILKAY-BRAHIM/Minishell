/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:10:04 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/10 14:33:19 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTING_H
# define BUILTING_H

# include "../minishell.h"

void	print_help(t_table *table, int i);
void	not_valid(char *cmd, char *arg, int type);
int		ft_echo(t_table *table, t_env *env);
int		ft_env(t_table *table, t_env *env);
int		ft_cd(t_table *table, t_env *env);
int		ft_export(t_table *table, t_env *env);
int		ft_pwd(t_table *table, t_env *env);
int		ft_exit(t_table *table, t_env *env);
int		ft_unset(t_table *table, t_env *env);
void	ft_execute(t_table *table, t_env *env);
int		check_valid_name(char *name);
void	redirection(t_table *table);
int		execute_commande(t_table *table, t_env *env, int i);
int		pipex(t_tree *tree, t_env *env);
void	get_here_docs(t_tree *tree, t_env *env);

#endif