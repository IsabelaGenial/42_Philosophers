/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:22:29 by igenial           #+#    #+#             */
/*   Updated: 2024/02/14 14:38:12 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdint.h>

enum						e_philo_state
{
	HAS_FORK,
	EATING,
	SLEEPING,
	THINKING,
	DEAD
};

typedef struct	s_inf
{
	int	nu_philos;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int each_philos_eat;
}	t_inf;

typedef struct s_philo_state
{
	enum	e_philo_state mode;
	long 	time;
}	t_philo_state;

typedef struct s_philo
{
	int 				id;
	pthread_t 			*pthread;
	t_philo_state 		state;
	int 				eat_n;
	long 				last_eat_time;

}	t_philo;

typedef struct s_main
{
	t_inf					*info;
	t_philo					*philo;
	t_philo_state			state;
	int						dead_philo;
	pthread_mutex_t			*forks;
	pthread_mutex_t			mx_phlio_state;
	pthread_mutex_t			mx_each_ate_enough;
	pthread_mutex_t			mx_dead_philo;
	pthread_mutex_t			mx_print;
}	t_main;

typedef struct s_thread
{
	int		i;
	t_main	dinning;
}	t_thread;

t_thread	*ig_init_thread_table(t_main *dining);
t_main		*ig_init_dinner(int argc, char **args);
void		*ig_philo_thread(void *param);
void 		ig_threads(t_main *dinner);
void		ig_check_forks(t_thread *dinner, int captor, int both );
int     	ig_atoi(const char *string);
int    		ig_check_args(int argc, char **args);
int			ig_check_thread(t_thread *dinner, int closer);
void		ig_state(t_thread *dinner, enum e_philo_state mode);
#endif
