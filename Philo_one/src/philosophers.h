/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laballea <laballea@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/17 08:57:10 by laballea          #+#    #+#             */
/*   Updated: 2021/01/25 09:51:43 by laballea         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct		s_data
{
	int				number_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				t_philo_must_eat;
	long			time;
	pthread_mutex_t std_out;
	pthread_mutex_t *mutex_eat;
	pthread_t		*id;
}					t_data;

typedef struct		s_d_philo
{
	int				id;
	pthread_mutex_t *fork;
	t_data			*data;
	long			last_eat;
	int				eat;
	int				m_eat;
	int				*dead;
}					t_d_philo;

void				ft_putstr_fd(char *s, int fd);
int					ft_atoi(const char *str);
t_d_philo			*ft_lstnew(int id, t_data *data,
					pthread_mutex_t **fork, int *dead);
void				gest_inf(int index, t_d_philo *philo, int died);
long				get_time();
size_t				ft_strlen(const char *s);
void				ft_putstr_fd(char *s, int fd);
void				str_buf(char *result, char *s, int *index);
void				init_philo(t_data data, pthread_mutex_t *fork,
					pthread_t *id);
void				init_mutex(pthread_mutex_t *fork, t_data data);
int					ft_error(char *str, int i);
long				get_time(long begin);
void				*monitor(void *arg);
void				*begin(void *arg);
void				ft_usleep(long n);
void				*monitor_test(t_d_philo **philos, t_data data);
void				ft_died(t_data data, t_d_philo *philo, int *dead);
void				ft_free(t_data data, t_d_philo *philo);
#endif
