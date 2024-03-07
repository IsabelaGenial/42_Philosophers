/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:18:13 by igenial           #+#    #+#             */
/*   Updated: 2024/03/07 16:41:59 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	ig_the_check(t_main *dinner)
{
	pthread_mutex_lock(&dinner->mx_each_ate_enough);
	pthread_mutex_lock(&dinner->mx_dead_philo);
	if (dinner->dead_philo != -1 || dinner->each_philos_eat != 0)
	{
		pthread_mutex_unlock(&dinner->mx_each_ate_enough);
		pthread_mutex_unlock(&dinner->mx_dead_philo);
		return (1);
	}
	pthread_mutex_unlock(&dinner->mx_each_ate_enough);
	pthread_mutex_unlock(&dinner->mx_dead_philo);
	return (0);
}

int	ig_philo_dead(t_philo *philo, long time_die)
{
	long	dead;

	dead = get_time();
	pthread_mutex_lock(&philo->ptr_main->mx_state);
	if (dead - philo->last_eat_time >= time_die)
	{
		dead = dead - philo->last_eat_time;
		philo->state = (t_philo_state){DEAD, dead};
		print_state(philo, DEAD);
		pthread_mutex_unlock(&philo->ptr_main->mx_state);
		return (1);
	}
	pthread_mutex_unlock(&philo->ptr_main->mx_state);
	return (0);
}

int	ig_philo_n_eat(t_philo *philo, int each_philos_eat)
{
	pthread_mutex_lock(&philo->ptr_main->mx_state);
	if (philo->eat_n == each_philos_eat)
	{
		pthread_mutex_unlock(&philo->ptr_main->mx_state);
		return (1);
	}
	pthread_mutex_unlock(&philo->ptr_main->mx_state);
	return (0);
}
