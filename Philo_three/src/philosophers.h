/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laballea <laballea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 08:57:10 by laballea          #+#    #+#             */
/*   Updated: 2021/01/25 10:14:01 by laballea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include <time.h>
# include <signal.h>
# include <sys/wait.h>

typedef struct		s_data
{
	int				number_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				t_philo_must_eat;
	long			time;
	sem_t			*std_out;
	sem_t			**eat;
	int				died;
	int				p_ate;
}					t_data;

typedef struct		s_d_philo
{
	int				id;
	sem_t			*fork;
	t_data			*data;
	long			last_eat;
	int				eat;
	int				m_eat;
	int				*dead;
	pid_t			pid;
}					t_d_philo;

void				ft_putstr_fd(char *s, int fd);
int					ft_atoi(const char *str);
t_d_philo			*ft_lstnew(int id, t_data *data,
					sem_t *fork, int *dead);
void				gest_inf(int index, t_d_philo *philo, int died);
long				get_time();
size_t				ft_strlen(const char *s);
void				ft_putstr_fd(char *s, int fd);
void				str_buf(char *result, char *s, int *index);
void				init_philo(t_data data, sem_t *forks);
int					ft_error(char *str, int i);
long				get_time(long begin);
void				*monitor(void *arg);
void				*begin(void *arg);
void				ft_usleep(long n);
void				ft_free(t_data *data);
#endif
