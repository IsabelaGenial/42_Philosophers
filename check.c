/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:18:13 by igenial           #+#    #+#             */
/*   Updated: 2024/03/04 19:54:58 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ig_state(t_philo *philo, enum e_philo_state mode)
{
	long	time;
	long	now;

	now = get_time();
	time = now - philo->ptr_main->time_start;
	pthread_mutex_lock(&philo->ptr_main->mx_state);
	philo->state = (t_philo_state){mode, time};
	pthread_mutex_unlock(&philo->ptr_main->mx_state);
	print_state(philo, mode);
}

int	ig_check_forks(t_main *dinner, int captor, int both )
{
	if (ig_the_check(dinner))
	{
		pthread_mutex_unlock(&dinner->forks[captor]);
		if (both)
			pthread_mutex_unlock(&dinner->forks[both]);
		return (1);
	}
	return (0);
}

void	print_state(t_philo *philo, enum e_philo_state mode)
{
	if(!ig_the_check(philo->ptr_main))
	{
		pthread_mutex_lock(&philo->ptr_main->mx_print);
		printf("%ld %d %s\n", get_time() - philo->ptr_main->time_start, philo->id + 1,
			   (char[5][20]) {"has taken a fork", "is eating", "is sleeping",
							  "is thinking", "died"}[mode]);
		pthread_mutex_unlock(&philo->ptr_main->mx_print);
	}

}
