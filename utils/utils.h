/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 06:14:07 by rrasezin          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2023/04/05 12:40:34 by bchifour         ###   ########.fr       */
=======
/*   Updated: 2023/04/02 00:58:54 by rrasezin         ###   ########.fr       */
>>>>>>> adcbe6a56695efca909c06bedf216636714f7f07
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
<<<<<<< HEAD
char	*ft_strjoin(char *s1, char *s2);
=======
char	*ft_strchr(const char *s, int c);
t_env	*new_list(char *org_env);
void	add_back(t_env **list, t_env *new);
void	add_front(t_env **list, t_env *new);
>>>>>>> adcbe6a56695efca909c06bedf216636714f7f07

#endif