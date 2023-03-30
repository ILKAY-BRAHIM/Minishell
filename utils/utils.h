/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bchifour <bchifour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/25 06:14:07 by rrasezin          #+#    #+#             */
/*   Updated: 2023/03/30 07:09:35 by bchifour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include <stdlib.h>

char	**ft_split(char *s, char c, int *tfo);
char	*ft_substr(char *s, unsigned int start, size_t len);
size_t	ft_strlen(const char *src);

#endif