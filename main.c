/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 13:56:05 by igenial           #+#    #+#             */
/*   Updated: 2024/03/07 17:19:16 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **args)
{
	t_main		*dining_philos;

	if (ig_check_args(argc, args))
		return (1);
	dining_philos = ig_init_dinner(argc, args);
	if (!dining_philos)
		return (printf("error malloc"));
	ig_threads(dining_philos);
	dining_philos->time_start = get_time();
	if (dining_philos->info->nu_philos == 1)
		ig_creat_lonely(dining_philos);
	else
		ig_creat_thread(dining_philos);
	exit_thread(dining_philos);
	return (0);
}
