/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laballea <laballea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 08:50:12 by laballea          #+#    #+#             */
/*   Updated: 2021/01/25 10:21:40 by laballea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t		ft_strlen(const char *s)
{
	size_t	size;

	size = 0;
	while (*s++)
		size++;
	return (size);
}

void		ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void		str_buf(char *result, char *s, int *index)
{
	int n;

	n = 0;
	while (s[n])
		result[(*index)++] = s[n++];
}

int			ft_error(char *str, int i)
{
	ft_putstr_fd(str, 2);
	return (i);
}
