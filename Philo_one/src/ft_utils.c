/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laballea <laballea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 08:49:51 by laballea          #+#    #+#             */
/*   Updated: 2021/01/20 13:24:42 by laballea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		nbr_buf(char *result, int *index, long long n)
{
	long long div;

	div = 1;
	if (!n)
		result[(*index)++] = '0';
	while (div <= n)
		div *= 10;
	div = div / 10;
	while (div)
	{
		result[(*index)++] = (n / div) % 10 + '0';
		div /= 10;
	}
}

void		print_inf(long time, char *str, int id)
{
	char	result[1024];
	int		i;

	i = 0;
	nbr_buf(result, &i, time);
	str_buf(result, "ms ", &i);
	nbr_buf(result, &i, id);
	str_buf(result, str, &i);
	write(1, result, i);
}

void		gest_inf(int index, t_d_philo *philo, int died)
{
	long time;

	pthread_mutex_lock(&philo->data->std_out);
	time = get_time(philo->data->time);
	if (index == 0)
		print_inf(time, " as taken a fork\n", philo->id);
	else if (index == 1)
		print_inf(time, " is eating\n", philo->id);
	else if (index == 2)
		print_inf(time, " is sleeping\n", philo->id);
	else if (index == 3)
		print_inf(time, " is thinking\n", philo->id);
	else if (index == 4)
		print_inf(time, " died\n", philo->id);
	else if (index == 5)
		print_inf(time, " eat enought\n", philo->id);
	if (!died)
		pthread_mutex_unlock(&philo->data->std_out);
}

t_d_philo	*ft_lstnew(int id, t_data *data, pthread_mutex_t **fork, int *dead)
{
	t_d_philo *list;

	if (!(list = malloc(sizeof(t_d_philo))))
		return (0);
	list->id = id;
	list->data = data;
	list->fork = (*fork);
	list->dead = dead;
	return (list);
}

int			ft_atoi(const char *str)
{
	int		neg;
	long	result;

	neg = 1;
	result = 0;
	while (*str == ' ' || *str == '\t' || *str == '\v'
	|| *str == '\n' || *str == '\r' || *str == '\f')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			neg = -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		result = result * 10 + (*str - 48);
		str++;
	}
	return (result * neg);
}
