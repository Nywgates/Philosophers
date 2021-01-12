/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laballea <laballea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 08:44:46 by laballea          #+#    #+#             */
/*   Updated: 2020/09/17 09:11:48 by laballea         ###   ########.fr       */
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
	pthread_mutex_init(&data->std_out, NULL);
	if (argc == 6)
		data->t_philo_must_eat = ft_atoi(str[5]);
	else
		data->t_philo_must_eat = -1;
}

int			ft_eat(t_d_philo *philo)
{
	pthread_mutex_lock(&philo->fork[philo->id]);
	gest_inf(get_time(philo->data->time), 0, philo);
	pthread_mutex_lock(&philo->fork[(philo->id + 1)
	% philo->data->number_philo]);
	gest_inf(get_time(philo->data->time), 0, philo);
	gest_inf(get_time(philo->data->time), 1, philo);
	philo->m_eat++;
	philo->last_eat = get_time(philo->data->time);
	usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->fork[(philo->id + 1)
	% philo->data->number_philo]);
	pthread_mutex_unlock(&philo->fork[philo->id]);
	return (0);
}

void		*begin(void *arg)
{
	t_d_philo *philo;

	philo = (t_d_philo *)arg;
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
			gest_inf(get_time(philo->data->time), 4, philo);
			pthread_mutex_lock(&philo->data->std_out);
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
	pthread_mutex_t *mutex;
	pthread_mutex_t *fork;

	if (argc < 5)
		return (ft_error("Not enought argument.\n", 1));
	parse(&data, argv, argc);
	id = malloc(sizeof(pthread_t) * (data.number_philo));
	id_mono = malloc(sizeof(pthread_t) * (data.number_philo));
	fork = malloc(sizeof(pthread_mutex_t) * (data.number_philo));
	mutex = malloc(sizeof(pthread_mutex_t) * (data.number_philo));
	init_mutex(fork, mutex, data);
	init_philo(data, fork, id, id_mono);
}
