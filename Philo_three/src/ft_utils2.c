/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laballea <laballea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 08:45:33 by laballea          #+#    #+#             */
/*   Updated: 2020/09/23 10:14:36 by laballea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void		wait_child(t_d_philo **lst_struct, int n_philo)
{
	int status;
	int i;

	(void)lst_struct;
	(void)n_philo;
	while (1)
	{
		status = 0;
		if (waitpid(-1, &status, 0) < 0 || WIFEXITED(status))
		{
			i = -1;
			while (++i < n_philo)
				kill(lst_struct[i]->pid, SIGINT);
			exit(WEXITSTATUS(status));
		}
	}
}

void		init_philo(t_data data, sem_t *forks,
			pthread_t *id, pthread_t *id_mono)
{
	int			i;
	t_d_philo	**lst_struct;
	int			dead;
	int			state;
	int dt;

	dead = 0;
	lst_struct = malloc(sizeof(t_d_philo **) * data.number_philo);
	i = 0;
	while (i < data.number_philo)
	{
		lst_struct[i] = ft_lstnew(i, &data, forks, &dead);
		if (!(lst_struct[i]->pid = fork()))
			begin(lst_struct[i]);
		i++;
	}
	i = 0;
	wait_child(lst_struct, data.number_philo);
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
