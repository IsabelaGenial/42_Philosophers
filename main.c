/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:56:05 by igenial           #+#    #+#             */
/*   Updated: 2024/02/14 14:22:17 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **args)
{
	t_main		*dining_philos;
	int			i;
	t_philo		philo;

	if(ig_check_args(argc, args))
		return (0);
	dining_philos = ig_init_dinner(argc, args);
	if(!dining_philos)
		return(printf("error malloc"));
	ig_threads(dining_philos);
	dining_philos->time_start = get_time();
	ig_creat_thread(dining_philos);
	waiter(dining_philos);
	i = 0;
	while (i < dining_philos->info->nu_philos)
	{
		philo = dining_philos->philo[i++];
		pthread_join(philo.pthread, NULL);
	}
	return(printf("\nsai MAIN\n"));
	return(0);
}
