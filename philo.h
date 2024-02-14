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

typedef struct	s_inf
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int times_each_philosopher_eat;
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
	struct s_philo	*next;

}	t_philo;

typedef struct s_main
{
	t_inf					info;
	t_philo					philo;
	int						dead_philo;
	pthread_mutex_t			*forks;
	pthread_mutex_t			mx_phlio_state;
	pthread_mutex_t			mx_each_ate_enough;
	pthread_mutex_t			mx_dead_philo;
	pthread_mutex_t			mx_print;
}	t_main;

#endif
