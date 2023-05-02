/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 06:14:07 by rrasezin          #+#    #+#             */
/*   Updated: 2023/04/29 15:40:14 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>

typedef struct s_env
{
	char			*name;
	char			*value;
	struct s_env	*next;
}			t_env;

char	**ft_split(char *s, char c);
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlen(char *src);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *src, size_t len);
int		ft_strcmp(char *s1, char *s2);
void	ft_putstr(char *str);
char	*ft_strdup(char *s1);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strncmp(char *s1, char *s2, size_t n);
int		ft_isdigit(int src);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	*ft_strnchr(char *s, char first, char end, int count);
int		word_count(const char *s, char c);

#endif