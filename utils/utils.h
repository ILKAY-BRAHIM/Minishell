/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrasezin <rrasezin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 06:14:07 by rrasezin          #+#    #+#             */
/*   Updated: 2023/04/05 15:07:31 by rrasezin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "../minishell.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

char	**ft_split(char *s, char c, int *tfo);
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *src);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *src, size_t len);
int		ft_strcmp(char *s1, char *s2);
void	ft_putstr(char *str);
char	*ft_strdup(char *s1);
char	*ft_strchr(const char *s, int c);

t_env	*new_list(char *org_env);
void	add_back(t_env **list, t_env *new);
void	add_front(t_env **list, t_env *new);
#endif