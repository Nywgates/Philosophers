/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 08:44:46 by laballea          #+#    #+#             */
/*   Updated: 2021/01/22 16:13:50 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		parse(t_data *data, char **str, int argc)
{
	int		i;
	char	name[1];

	i = 0;
	data->number_philo = ft_atoi(str[1]);
	data->time_to_die = ft_atoi(str[2]);
	data->time_to_eat = ft_atoi(str[3]);
	data->time_to_sleep = ft_atoi(str[4]);
	data->time = get_time(0);
	data->died = 0;
	sem_unlink("std_out");
	data->std_out = sem_open("std_out", O_CREAT, 0666, 1);
	data->eat = malloc(sizeof(sem_t *) * (data->number_philo));
	while (i < data->number_philo)
	{
		name[0] = (i + 48) + '0';
		sem_unlink(name);
		data->eat[i++] = sem_open(name, O_CREAT, 0666, 1);
	}
	if (argc == 6)
		data->t_philo_must_eat = ft_atoi(str[5]);
	else
		data->t_philo_must_eat = -1;
}

int			ft_eat(t_d_philo *philo)
{
	sem_wait(philo->fork);
	gest_inf(0, philo, 0);
	sem_wait(philo->fork);
	gest_inf(0, philo, 0);
	gest_inf(1, philo, 0);
	sem_wait(philo->data->eat[philo->id]);
	philo->m_eat++;
	philo->last_eat = get_time(philo->data->time);
	ft_usleep(philo->data->time_to_eat * 1000);
	sem_post(philo->data->eat[philo->id]);
	sem_post(philo->fork);
	sem_post(philo->fork);
	return (0);
}

void		*begin(void *arg)
{
	t_d_philo *philo;

	philo = (t_d_philo *)arg;
	philo->eat = 0;
	philo->m_eat = 0;
	philo->last_eat = get_time(philo->data->time);
	while (1)
	{
		gest_inf(3, philo, 0);
		ft_eat(philo);
		if (philo->eat)
			break ;
		gest_inf(2, philo, 0);
		ft_usleep(philo->data->time_to_sleep * 1000);
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
			sem_wait(philo->data->eat[philo->id]);
			gest_inf(4, philo, 1);
			sem_post(philo->data->eat[philo->id]);
			exit(0);
		}
		if (philo->m_eat == philo->data->t_philo_must_eat)
		{
			philo->eat = 1;
			gest_inf(5, philo, 0);
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

	if (argc < 5 || argc > 6)
		return (ft_error("Not valid arguments.\n", 1));
	parse(&data, argv, argc);
	id = malloc(sizeof(pthread_t) * (data.number_philo));
	id_mono = malloc(sizeof(pthread_t) * (data.number_philo));
	sem_unlink("fork");
	fork = sem_open("fork", O_CREAT, 0666, data.number_philo);
	init_philo(data, fork, id, id_mono);
}
