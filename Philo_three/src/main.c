/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laballea <laballea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 08:44:46 by laballea          #+#    #+#             */
/*   Updated: 2020/09/23 10:18:01 by laballea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		parse(t_data *data, char **str, int argc)
{
	data->number_philo = ft_atoi(str[1]);
	data->time_to_die = ft_atoi(str[2]);
	data->time_to_eat = ft_atoi(str[3]);
	data->time_to_sleep = ft_atoi(str[4]);
	data->time = get_time(0);
	sem_unlink("std_out");
	data->std_out = sem_open("std_out", O_CREAT, 0666, 1);
	sem_unlink("dead");
	data->dead = sem_open("dead", O_CREAT, 0666, 1);
	if (argc == 6)
		data->t_philo_must_eat = ft_atoi(str[5]);
	else
		data->t_philo_must_eat = -1;
}

int			ft_eat(t_d_philo *philo)
{
	sem_wait(philo->fork);
	gest_inf(get_time(philo->data->time), 0, philo);
	sem_wait(philo->fork);
	gest_inf(get_time(philo->data->time), 0, philo);
	gest_inf(get_time(philo->data->time), 1, philo);
	philo->m_eat++;
	philo->last_eat = get_time(philo->data->time);
	usleep(philo->data->time_to_eat * 1000);
	sem_post(philo->fork);
	sem_post(philo->fork);
	return (0);
}

void		*begin(void *arg)
{
	t_d_philo *philo;
	pthread_t mono;
	struct timespec tim, tim2;

	tim.tv_sec = 1;
   	tim.tv_nsec = 500;

	philo = (t_d_philo *)arg;
	pthread_create(&mono, NULL, &monitor, philo);
	philo->eat = 0;
	philo->m_eat = 0;
	philo->last_eat = philo->data->time;
	while (1)
	{
		gest_inf(get_time(philo->data->time), 3, philo);
		ft_eat(philo);
		if (philo->eat)
			break ;
		gest_inf(get_time(philo->data->time), 2, philo);
		usleep(philo->data->time_to_sleep * 1000);
	}
	exit(0);
	return (NULL);
}

void		*monitor(void *arg)
{
	t_d_philo *philo;

	philo = (t_d_philo *)arg;
	while (1)
	{
		if (get_time(philo->data->time) - philo->last_eat
		> philo->data->time_to_die)
		{
			sem_wait(philo->data->dead);
			gest_inf(get_time(philo->data->time), 4, philo);
			exit(0);
		}
		if (philo->m_eat == philo->data->t_philo_must_eat)
		{
			philo->eat = 1;
			gest_inf(get_time(philo->data->time), 5, philo);
			break ;
		}
	}
	return (NULL);
}

int			main(int argc, char **argv)
{
	t_data			data;
	pthread_t		*id;
	pthread_t		*id_mono;
	sem_t			*fork;

	if (argc < 5)
		return (ft_error("Not enought argument.\n", 1));
	parse(&data, argv, argc);
	id = malloc(sizeof(pthread_t) * (data.number_philo));
	id_mono = malloc(sizeof(pthread_t) * (data.number_philo));
	sem_unlink("fork");
	fork = sem_open("fork", O_CREAT, 0666, data.number_philo);
	init_philo(data, fork, id, id_mono);
}
