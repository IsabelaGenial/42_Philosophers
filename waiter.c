/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   waiter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 17:23:54 by igenial           #+#    #+#             */
/*   Updated: 2024/03/07 17:25:59 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	waiter(t_main *dinner)
{
	int	philo;

	while (369)
	{
		philo = the_philo_die(dinner);
		if (philo > -1)
		{
			pthread_mutex_lock(&dinner->mx_dead_philo);
			dinner->dead_philo = philo;
			pthread_mutex_unlock(&dinner->mx_dead_philo);
			break ;
		}
		if (dinner->info->each_philos_eat
			&& the_philo_eat(dinner) == dinner->info->nu_philos - 1)
		{
			pthread_mutex_lock(&dinner->mx_each_ate_enough);
			dinner->each_philos_eat = the_philo_eat(dinner);
			pthread_mutex_unlock(&dinner->mx_each_ate_enough);
			break ;
		}
	}
	return (0);
}

int	the_philo_die(t_main *dinner)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&dinner->mx_phlio_state);
	while (i < dinner->info->nu_philos)
	{
		if (ig_philo_dead(&dinner->philo[i], dinner->info->time_to_die))
		{
			pthread_mutex_unlock(&dinner->mx_phlio_state);
			return (i);
		}
		i++;
	}
	pthread_mutex_unlock(&dinner->mx_phlio_state);
	return (-1);
}

int	the_philo_eat(t_main *dinner)
{
	int	i;
	int	eat;

	i = 0;
	eat = 0;
	pthread_mutex_lock(&dinner->mx_phlio_state);
	while (i < dinner->info->nu_philos)
	{
		if (ig_philo_n_eat(&dinner->philo[i], dinner->info->each_philos_eat))
			eat++;
		i++;
	}
	pthread_mutex_unlock(&dinner->mx_phlio_state);
	return (eat);
}
