#include "philo.h"

int ig_check_thread(t_thread *dinner, int closer)
{
	pthread_mutex_lock(&dinner->dinning.mx_dead_philo);
	pthread_mutex_lock(&dinner->dinning.mx_each_ate_enough);
	if (dinner->dinning.dead_philo > -1
		|| dinner->dinning.info->each_philos_eat)
	{
		pthread_mutex_unlock(&dinner->dinning.mx_each_ate_enough);
		pthread_mutex_unlock(&dinner->dinning.mx_dead_philo);
		if(closer)
		{
			free(dinner);
			exit(closer);
		}
		return (1);
	}
	pthread_mutex_unlock(&dinner->dinning.mx_each_ate_enough);
	pthread_mutex_unlock(&dinner->dinning.mx_dead_philo);
	return (0);
}