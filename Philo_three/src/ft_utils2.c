/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laballea <laballea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 08:45:33 by laballea          #+#    #+#             */
/*   Updated: 2021/01/25 10:21:46 by laballea         ###   ########.fr       */
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
			if (WEXITSTATUS(status) == 0)
			{
				while (++i < n_philo)
					kill(lst_struct[i]->pid, SIGINT);
			}
			exit(WEXITSTATUS(status));
		}
	}
}

void		init_philo(t_data data, sem_t *forks)
{
	int			i;
	t_d_philo	**lst_struct;
	int			dead;

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
	wait_child(lst_struct, data.number_philo);
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

void		ft_free(t_data *data)
{
	int i;

	i = -1;
	free(data->eat);
	exit(0);
}
