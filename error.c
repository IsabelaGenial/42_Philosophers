/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igenial <igenial@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:18:24 by igenial           #+#    #+#             */
/*   Updated: 2024/02/26 13:18:26 by igenial          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

static int  is_num(char *args);

int ig_check_args(int argc, char **args)
{
	if (argc != 6 && argc != 5)
		return(printf("ERROR: number of arguments\n"));
	if (is_num(args[1]) || is_num(args[2]) || is_num(args[3])
		|| is_num(args[4]) || (argc == 6 && is_num(args[5])))
		return (printf("ERROR: arguments\n"));
	if (ig_atoi(args[1]) < 0)
		return (printf("ERROR: number of philosopher\n"));
	if (ig_atoi(args[2]) < 0 || ig_atoi(args[3]) < 0
		|| ig_atoi(args[4]) < 0 || (argc == 6 && ig_atoi(args[5]) < 0))
		return (printf("ERROR: number of times\n"));
	return (0);
}

static int  is_num(char *args)
{
	while((*args >= '0' && *args <= '9') || (*args == '-' || *args == '+'))
		args++;
	return (*args);
}
