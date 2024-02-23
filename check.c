#include "philo.h"

int ig_check_thread(t_main *main, int closer)
{
	pthread_mutex_lock(&main->mx_dead_philo);
	pthread_mutex_lock(&main->mx_each_ate_enough);
	if (main->dead_philo > -1
		|| main->info->each_philos_eat)
	{
		pthread_mutex_unlock(&main->mx_each_ate_enough);
		pthread_mutex_unlock(&main->mx_dead_philo);
		if(closer)
		{
			//free(dinner);
			exit(closer);
		}
		return (1);
	}
	pthread_mutex_unlock(&main->mx_each_ate_enough);
	pthread_mutex_unlock(&main->mx_dead_philo);
	return (0);
}

void ig_state(t_philo *philo, enum e_philo_state mode)
{
	struct timeval time;
	long get_time;

//	ig_check_thread(philo->ptr_main, 1);
	gettimeofday(&time, NULL);
	get_time = ((time.tv_sec * 1000L) + (time.tv_usec / 1000L));
	philo->state = (t_philo_state){mode, get_time};
	pthread_mutex_lock(&philo->ptr_main->mx_print);
	printf("%ld %d %s\n", get_time, philo->id + 1,
		   (char [5][20]){"has taken a fork", "is eating", "is sleeping",
			"is thinking", "died"}[mode]);
	pthread_mutex_unlock(&philo->ptr_main->mx_print);
}

void ig_check_forks(t_main *dinner, int captor, int both )
{
	if(ig_check_thread(dinner, 0))
	{
		pthread_mutex_unlock(&dinner->forks[captor]);
		if (both)
			pthread_mutex_unlock(&dinner->forks[both]);
		exit(0);
	}
}