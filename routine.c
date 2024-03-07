/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:26:33 by igenial           #+#    #+#             */
/*   Updated: 2024/03/07 17:32:32 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ig_eat(t_philo *philo, enum e_philo_state mode);
static void	ig_sleep(t_philo *philo, enum e_philo_state mode);

void	*ig_philo_thread(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	while (!ig_the_check(philo->ptr_main))
	{
		if (!ig_the_check(philo->ptr_main))
			ig_state(philo, THINKING);
		usleep(10);
		if (!ig_the_check(philo->ptr_main))
			ig_eat(philo, EATING);
		if (!ig_the_check(philo->ptr_main))
			ig_sleep(philo, SLEEPING);
	}
	return (0);
}

static void	ig_eat(t_philo *philo, enum e_philo_state mode)
{
	int	first_fork;
	int	second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->id;
		second_fork = philo->id - 1;
		if (philo->id == 0)
			second_fork = philo->ptr_main->info->nu_philos - 1;
	}
	else
	{
		first_fork = philo->id - 1;
		second_fork = philo->id;
		usleep(10);
	}
	if (take_fork(philo, first_fork, second_fork, mode))
		return ;
	pthread_mutex_lock(&philo->ptr_main->mx_state);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->ptr_main->mx_state);
	usleep(philo->ptr_main->info->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->ptr_main->forks[first_fork]);
	pthread_mutex_unlock(&philo->ptr_main->forks[second_fork]);
}

static void	ig_sleep(t_philo *philo, enum e_philo_state mode)
{
	if (!ig_the_check(philo->ptr_main))
	{
		ig_state(philo, mode);
		pthread_mutex_lock(&philo->ptr_main->mx_state);
		philo->eat_n++;
		pthread_mutex_unlock(&philo->ptr_main->mx_state);
		if (philo->ptr_main->info->time_to_sleep)
			usleep(philo->ptr_main->info->time_to_sleep * 1000);
	}
	return ;
}

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

int	take_fork(t_philo *philo, int first, int second, enum e_philo_state mode)
{
	if (ig_the_check(philo->ptr_main))
		return (1);
	pthread_mutex_lock(&philo->ptr_main->forks[first]);
	ig_state(philo, HAS_FORK);
	if (ig_check_forks(philo->ptr_main, first, 0))
		return (1);
	pthread_mutex_lock(&philo->ptr_main->forks[second]);
	ig_state(philo, HAS_FORK);
	if (ig_check_forks(philo->ptr_main, first, second))
		return (1);
	ig_state(philo, mode);
	return (0);
}
