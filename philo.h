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

typedef struct s_fork
{
	//malloc mutex
	pthread_mutex_t			forks;
	int 					id;
} t_fork;

typedef struct s_main
{
	t_inf					*info;
	t_philo					*philo;
	int						dead_philo;
	t_fork 					**fork;
	pthread_mutex_t			mx_phlio_state;
	pthread_mutex_t			mx_each_ate_enough;
	pthread_mutex_t			mx_dead_philo;
	pthread_mutex_t			mx_print;
	//variable - time started routine struct timeval
	//atomic

}	t_main;

typedef struct s_thread
{
	int		i;
	t_main	dinning;
}	t_thread;

t_main	*ig_init_dinner(int argc, char **args);
int     ig_atoi(const char *string);
int     ig_check_args(int argc, char **args);

#endif
