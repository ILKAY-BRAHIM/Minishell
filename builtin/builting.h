/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builting.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 16:10:04 by rrasezin          #+#    #+#             */
/*   Updated: 2023/05/17 18:39:02 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTING_H
# define BUILTING_H

# include "../minishell.h"

typedef struct s_pipe
{
	int	p_1[2];
	int	p_2[2];
	int	*id;
	int	i;
	int	j;
	int	size;
	int	status;
}			t_pipe;

int		print_help(t_table *table, int i);
int		not_valid(char *cmd, char *arg, int type);
int		ft_echo(t_table *table, t_env **env);
int		ft_env(t_table *table, t_env **env);
int		ft_cd(t_table *table, t_env **env);
int		without_args(t_env *env);
int		ft_export(t_table *table, t_env **env);
int		ft_pwd(t_table *table, t_env **env);
int		ft_exit(t_table *table, t_env **env);
int		ft_unset(t_table *table, t_env **env);
char	**ft_get_env(t_env *list_env);
void	normal_execute(t_table *table, t_env **env, char *path);
void	no_path_execution(t_table *table, t_env **env, char **path);
void	call_execve(t_table *table, char *path, char **env);
void	ft_execute(t_table *table, t_env **env);
int		check_valid_name(char *name);
int		redirection(t_table *table);
int		execute_commande(t_table *table, t_env **env, int i);
void	close_parent_pipe(t_pipe *p);
void	close_open_pipe(t_pipe *p);
int		pipex(t_tree *tree, t_env **env);
void	get_here_docs(t_tree *tree, t_env *env);

#endif