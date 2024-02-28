/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:18:13 by igenial           #+#    #+#             */
/*   Updated: 2024/02/26 13:18:16 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ig_state(t_philo *philo, enum e_philo_state mode)
{
	long time;
	long now;

	now = get_time();
	printf("\n%ld\n", now);
	time = now - philo->ptr_main->time_start;
	printf("\n%ld\n", time);
	philo->state = (t_philo_state){mode, time};
	print_state(philo, mode);
}

void ig_check_forks(t_main *dinner, int captor, int both )
{
	if(ig_the_check(dinner,0))
	{
		pthread_mutex_unlock(&dinner->forks[captor]);
		if (both)
			pthread_mutex_unlock(&dinner->forks[both]);
		exit(printf("\nsai FORK\n"));
	}
}

void print_state(t_philo *philo, enum e_philo_state mode)
{
	pthread_mutex_lock(&philo->ptr_main->mx_print);
	printf("%ld %d %s\n", philo->state.time, philo->id + 1,
		   (char [5][20]){"has taken a fork", "is eating", "is sleeping",
						  "is thinking", "died"}[mode]);
	pthread_mutex_unlock(&philo->ptr_main->mx_print);
}