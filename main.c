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
	t_thread 	*dinner;
	int 		i;

	if(ig_check_args(argc, args))
		return (0);
	dining_philos = ig_init_dinner(argc, args);
	if(!dining_philos)
		return(printf("error malloc"));
	dinner = ig_init_thread_table(dining_philos);
	ig_threads(&dinner->dinning);
	i = 0;
	while (i < dinner->dinning.info->nu_philos)
		pthread_join(*dinner->dinning.philo[i++].pthread, NULL);
	free(dinner);
	return(0);
}
