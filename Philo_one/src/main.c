/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laballea <laballea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 08:44:46 by laballea          #+#    #+#             */
/*   Updated: 2021/01/25 13:08:29 by laballea         ###   ########.fr       */
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
	data->philos_eat = 0;
	data->mutex_eat = malloc(sizeof(pthread_mutex_t) * (data->number_philo));
	pthread_mutex_init(&data->std_out, NULL);
	if (argc == 6)
		data->t_philo_must_eat = ft_atoi(str[5]);
	else
		data->t_philo_must_eat = -1;
}

int			ft_eat(t_d_philo *philo)
{
	int		fork_one;
	int		fork_two;

	fork_one = philo->id;
	fork_two = (philo->id + 1) % philo->data->number_philo;
	pthread_mutex_lock(&philo->fork[fork_one]);
	gest_inf(0, philo, 0);
	pthread_mutex_lock(&philo->fork[fork_two]);
	gest_inf(0, philo, 0);
	pthread_mutex_lock(&philo->data->mutex_eat[philo->id]);
	gest_inf(1, philo, 0);
	philo->last_eat = get_time(philo->data->time);
	ft_usleep(philo->data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->data->mutex_eat[philo->id]);
	philo->m_eat++;
	pthread_mutex_unlock(&philo->fork[fork_two]);
	pthread_mutex_unlock(&philo->fork[fork_one]);
	return (0);
}

void		*begin(void *arg)
{
	t_d_philo *philo;

	philo = (t_d_philo *)arg;
	philo->eat = 0;
	philo->last_eat = get_time(philo->data->time);
	while (1)
	{
		gest_inf(3, philo, 0);
		if (philo->eat)
			break ;
		ft_eat(philo);
		gest_inf(2, philo, 0);
		ft_usleep(philo->data->time_to_sleep * 1000);
	}
	return (NULL);
}

int			main(int argc, char **argv)
{
	t_data			data;
	pthread_t		*id;
	pthread_mutex_t *fork;

	if (argc < 5 || argc > 6)
		return (ft_error("Not valid arguments.\n", 1));
	parse(&data, argv, argc);
	id = malloc(sizeof(pthread_t) * (data.number_philo));
	fork = malloc(sizeof(pthread_mutex_t) * (data.number_philo));
	init_mutex(fork, data);
	init_philo(data, fork, id);
}
