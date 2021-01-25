/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laballea <laballea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 09:36:48 by laballea          #+#    #+#             */
/*   Updated: 2021/01/25 13:14:56 by laballea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		ft_died(t_data data, t_d_philo *philo, int *dead)
{
	pthread_mutex_lock(&data.mutex_eat[philo->id]);
	gest_inf(4, philo, 1);
	ft_free(data, philo);
	*dead = 1;
	pthread_mutex_unlock(&data.mutex_eat[philo->id]);
}

void		ft_eat_mono(t_d_philo *philo)
{
	gest_inf(5, philo, 0);
	philo->eat = 1;
	philo->data->philos_eat++;
}

void		*monitor_test(t_d_philo **philos, t_data data)
{
	int			dead;
	int			i;
	t_d_philo	*philo;

	dead = 0;
	while (!dead)
	{
		i = -1;
		while (++i < data.number_philo)
		{
			philo = philos[i];
			if (get_time(data.time) - philo->last_eat
				> data.time_to_die && !philo->eat)
				ft_died(data, philo, &dead);
			if (philo->m_eat == data.t_philo_must_eat && !philo->eat)
				ft_eat_mono(philo);
		}
		if (philo->data->philos_eat == data.number_philo)
			ft_free(data, philo);
		ft_usleep(50);
	}
	return (NULL);
}

void		ft_free(t_data data, t_d_philo *philo)
{
	int i;

	i = -1;
	free(philo->fork);
	free(data.mutex_eat);
	free(data.id);
	exit(0);
}
