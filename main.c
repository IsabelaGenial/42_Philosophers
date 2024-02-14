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
	t_main dining_philos;

	if (argc != 6)
		return(0);
	else
	{
		dining_philos.info.number_of_philosophers = atoi(args[1]);
		dining_philos.info.time_to_die = atoi(args[2]);
		dining_philos.info.time_to_eat = atoi(args[3]);
		dining_philos.info.time_to_sleep = atoi(args[4]);
	}
	printf("%i\n",dining_philos.info.number_of_philosophers);
	printf("%i\n",dining_philos.info.time_to_die);
	printf("%i\n",dining_philos.info.time_to_eat);
	printf("%i\n",dining_philos.info.time_to_sleep);
	return(0);
}
