/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laballea <laballea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 08:45:33 by laballea          #+#    #+#             */
/*   Updated: 2021/01/20 11:25:52 by laballea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		init_philo(t_data data, sem_t *fork,
			pthread_t *id, pthread_t *id_mono)
{
	int			i;
	t_d_philo	**lst_struct;
	int			dead;

	dead = 0;
	lst_struct = malloc(sizeof(t_d_philo **) * data.number_philo);
	i = 0;
	while (i < data.number_philo)
	{
		lst_struct[i] = ft_lstnew(i, &data, fork, &dead);
		pthread_create(&id[i], NULL, begin, lst_struct[i]);
		pthread_create(&id_mono[i], NULL, monitor, lst_struct[i]);
		i++;
		usleep(10);
	}
	i = 0;
	while (i < data.number_philo)
	{
		pthread_join(id[i], NULL);
		pthread_join(id_mono[i], NULL);
		i++;
	}
}

int			ft_error(char *str, int i)
{
	ft_putstr_fd(str, 2);
	return (i);
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
