/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 12:45:19 by igenial           #+#    #+#             */
/*   Updated: 2024/03/07 17:18:24 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ig_creat_thread(t_main *main)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < main->info->nu_philos)
	{
		philo = &main->philo[i];
		pthread_create(&philo->pthread, NULL, ig_philo_thread, (void *)philo);
		i++;
	}
	waiter(main);
	i = 0;
	while (i < main->info->nu_philos)
	{
		pthread_mutex_lock(&main->mx_state);
		philo = &main->philo[i];
		pthread_mutex_unlock(&main->mx_state);
		pthread_join(philo->pthread, NULL);
		i++;
	}
}

void	ig_creat_lonely(t_main *main)
{
	t_philo	*philo;

	philo = &main->philo[0];
	pthread_create(&philo->pthread, NULL, ig_mr_lonely, (void *)philo);
	pthread_join(philo->pthread, NULL);
}

void	*ig_mr_lonely(void *param)
{
	t_philo	*philo;

	philo = (t_philo *)param;
	ig_state(philo, THINKING);
	usleep(100);
	pthread_mutex_lock(&philo->ptr_main->one_fork);
	pthread_mutex_unlock(&philo->ptr_main->one_fork);
	ig_state(philo, HAS_FORK);
	usleep(philo->ptr_main->info->time_to_die * 1000);
	ig_state(philo, DEAD);
	return (0);
}

void	print_state(t_philo *philo, enum e_philo_state mode)
{
	long	time;

	time = get_time() - philo->ptr_main->time_start;
	if (!ig_the_check(philo->ptr_main))
	{
		pthread_mutex_lock(&philo->ptr_main->mx_print);
		printf("%ld %d %s\n", time, philo->id + 1, (char [5][20])
		{"has taken a fork", "is eating", "is sleeping",
			"is thinking", "died"}[mode]);
		pthread_mutex_unlock(&philo->ptr_main->mx_print);
	}
}
