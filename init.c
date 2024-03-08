/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:18:34 by igenial           #+#    #+#             */
/*   Updated: 2024/03/07 16:58:11 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex_fork(t_main *main);

t_main	*ig_init_dinner(int argc, char **args)
{
	t_main	*dining_philos;

	dining_philos = (t_main *)malloc (sizeof(t_main));
	dining_philos->info = (t_inf *)malloc (sizeof(t_inf));
	dining_philos->info->nu_philos = ig_atoi(args[1]);
	dining_philos->info->time_to_die = ig_atoi(args[2]);
	dining_philos->info->time_to_eat = ig_atoi(args[3]);
	dining_philos->info->time_to_sleep = ig_atoi(args[4]);
	dining_philos->info->each_philos_eat = 0;
	if (argc == 6)
		dining_philos->info->each_philos_eat = ig_atoi(args[5]);
	dining_philos->dead_philo = -1;
	dining_philos->each_philos_eat = 0;
	dining_philos->forks = malloc(ig_atoi(args[1]) * sizeof(pthread_mutex_t));
	dining_philos->philo = (t_philo *)malloc (ig_atoi(args[1])
			* sizeof(t_philo));
	init_mutex_fork(dining_philos);
	pthread_mutex_init(&dining_philos->mx_each_ate_enough, NULL);
	pthread_mutex_init(&dining_philos->one_fork, NULL);
	pthread_mutex_init(&dining_philos->mx_phlio_state, NULL);
	pthread_mutex_init(&dining_philos->mx_state, NULL);
	pthread_mutex_init(&dining_philos->mx_dead_philo, NULL);
	pthread_mutex_init(&dining_philos->mx_print, NULL);
	return (dining_philos);
}

int	ig_atoi(const char *string)
{
	int	numb;
	int	neg;

	numb = 0;
	neg = 1;
	while ((*string >= 9 && *string <= 13) || *string == 32)
		string++;
	if (*string == '+' || *string == '-')
		if (*string++ == '-')
			neg = -1;
	while (*string >= '0' && *string <= '9')
		numb = (numb * 10) + ((*string++) - 48);
	return (numb * neg);
}

void	ig_threads(t_main *dinner)
{
	int		i;
	t_philo	*ptr_philo;

	i = 0;
	while (i < dinner->info->nu_philos)
	{
		ptr_philo = &dinner->philo[i];
		ptr_philo->id = i;
		ptr_philo->eat_n = 0;
		ptr_philo->last_eat_time = get_time();
		ptr_philo->ptr_main = dinner;
		i++;
	}
}

long	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	init_mutex_fork(t_main *main)
{
	int	i;

	i = 0;
	while (i < main->info->nu_philos)
	{
		pthread_mutex_init(&main->forks[i], NULL);
		i++;
	}
}
