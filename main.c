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
	t_main *dining_philos;

	ig_check_args(argc, args);
	dining_philos = ig_init_dinner(argc, args);
	if(!dining_philos)
		return(printf("error malloc"));

	return(0);
}
