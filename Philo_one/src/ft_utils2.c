/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laballea <laballea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 08:45:33 by laballea          #+#    #+#             */
/*   Updated: 2021/01/25 09:52:27 by laballea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		create_thread(t_data data, pthread_mutex_t *fork,
						pthread_t *id, t_d_philo **lst_struct)
{
	int i;
	int dead;

	dead = 0;
	i = 0;
	while (i < data.number_philo)
	{
		lst_struct[i] = ft_lstnew(i, &data, &fork, &dead);
		pthread_create(&id[i], NULL, begin, lst_struct[i]);
		i += 2;
	}
	usleep(1);
	i = 1;
	while (i < data.number_philo)
	{
		lst_struct[i] = ft_lstnew(i, &data, &fork, &dead);
		pthread_create(&id[i], NULL, begin, lst_struct[i]);
		i += 2;
	}
	data.id = id;
	monitor_test(lst_struct, data);
}

void		init_philo(t_data data, pthread_mutex_t *fork,
			pthread_t *id)
{
	int			i;
	t_d_philo	**lst_struct;

	lst_struct = malloc(sizeof(t_d_philo **) * data.number_philo);
	create_thread(data, fork, id, lst_struct);
	i = 0;
	while (i < data.number_philo)
	{
		pthread_join(id[i], NULL);
		free(lst_struct[i]);
		i++;
	}
}

void		init_mutex(pthread_mutex_t *fork, t_data data)
{
	int i;

	i = 0;
	while (i < data.number_philo)
	{
		pthread_mutex_init(&fork[i], NULL);
		pthread_mutex_init(&data.mutex_eat[i], NULL);
		i++;
	}
}

long		get_time(long begin)
{
	struct timeval	tv;
	long			time;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000;
	time += tv.tv_usec / 1000;
	if (begin == 0)
		return (time);
	else
		return (time - begin);
}

void		ft_usleep(long n)
{
	struct timeval	start;
	struct timeval	current;

	gettimeofday(&start, NULL);
	while (1)
	{
		usleep(50);
		gettimeofday(&current, NULL);
		if ((current.tv_sec - start.tv_sec) * 1000000 +
			(current.tv_usec - start.tv_usec) > n)
			break ;
	}
}
