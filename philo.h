/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 14:22:29 by igenial           #+#    #+#             */
/*   Updated: 2024/02/26 13:19:46 by igenial          ###   ########.fr       */
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

typedef struct s_main t_main;

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
	pthread_t 			pthread;
	t_philo_state 		state;
	int 				eat_n;
	t_main				*ptr_main;
	long 				last_eat_time;

}	t_philo;
//typedef struct s_thread
//{
//	int		i;
//	t_main	dinning;
//}	t_thread;
typedef struct s_main
{
	t_inf					*info;
	t_philo					*philo;
	t_philo_state			state;
	int						dead_philo;
	long 					time_start;
	int						each_philos_eat;
	pthread_mutex_t			*forks;
	pthread_mutex_t			mx_phlio_state;
	pthread_mutex_t			mx_each_ate_enough;
	pthread_mutex_t			mx_dead_philo;
	pthread_mutex_t			mx_print;
}	t_main;

t_main		*ig_init_thread_table(t_main *dining);
t_main		*ig_init_dinner(int argc, char **args);
void		*ig_philo_thread(void *param);
void 		ig_threads(t_main *dinner);
void		ig_check_forks(t_main *dinner, int captor, int both);
void		ig_state(t_philo *philo, enum e_philo_state mode);
void		ig_creat_thread(t_main *main);
void		print_state(t_philo *philo, enum e_philo_state mode);
int     	ig_atoi(const char *string);
int    		ig_check_args(int argc, char **args);
int			ig_check_thread(t_main *main, int closer);
int			ig_the_check(t_main *dinner, int the_end);
int 		waiter(t_main *dinner);
long		get_time(void);
#endif
