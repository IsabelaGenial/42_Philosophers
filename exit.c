/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:42:33 by igenial           #+#    #+#             */
/*   Updated: 2024/03/07 16:43:24 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_thread(t_main *main)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&main->mx_each_ate_enough);
	pthread_mutex_destroy(&main->one_fork);
	pthread_mutex_destroy(&main->mx_phlio_state);
	pthread_mutex_destroy(&main->mx_state);
	pthread_mutex_destroy(&main->mx_dead_philo);
	pthread_mutex_destroy(&main->mx_print);
	while (i < main->info->nu_philos)
		pthread_mutex_destroy(&main->forks[i++]);
	free(main->philo);
	free(main->forks);
	free(main->info);
	free(main);
}
