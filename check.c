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

void ig_state(t_thread *dinner, enum e_philo_state mode)
{
	struct timeval time;
	long get_time;

	ig_check_thread(dinner, 1);
	gettimeofday(&time, NULL);
	get_time = ((time.tv_sec * 1000L) + (time.tv_usec / 1000L));
	dinner->dinning.philo[dinner->i].state = (t_philo_state){mode, get_time};
	pthread_mutex_lock(&dinner->dinning.mx_print);
	printf("%ld %d %s\n", get_time, dinner->i + 1,
		   (char [5][20]){"has taken a fork", "is eating", "is sleeping",
			"is thinking", "died"}[mode]);
	pthread_mutex_unlock(&dinner->dinning.mx_print);
}

void ig_check_forks(t_thread *dinner, int captor, int both )
{
	if(ig_check_thread(dinner, 0))
	{
		pthread_mutex_unlock(&dinner->dinning.forks[captor]);
		if (both)
			pthread_mutex_unlock(&dinner->dinning.forks[both]);
		exit(0);
	}
}