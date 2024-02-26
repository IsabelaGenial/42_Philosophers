
#include "philo.h"

static void ig_eat(t_philo *philo, enum e_philo_state mode);
static void ig_sleep(t_philo *philo, enum e_philo_state mode);

void *ig_philo_thread(void *param)
{
	t_philo *philo;

	philo = (t_philo *)param;
	while(369)
	{
		ig_state(philo, THINKING);
		ig_eat(philo, EATING);
		ig_sleep(philo, SLEEPING);
	}
	//function dead;
	exit(0);
}

static void ig_eat(t_philo *philo, enum e_philo_state mode)
{
	int first_fork;
	int second_fork;

	if(philo->id % 2 == 0)
	{
		first_fork = philo->id;
		if ( philo->id == 0)
			second_fork = philo->ptr_main->info->nu_philos - 1;
		else
			second_fork = philo->id - 1;
	}
	else
	{
		first_fork = philo->id - 1;
		second_fork = philo->id;
	}
	pthread_mutex_lock(&philo->ptr_main->forks[first_fork]);
	ig_state(philo, HAS_FORK);
	pthread_mutex_lock(&philo->ptr_main->forks[second_fork]);
	ig_state(philo, HAS_FORK);
	ig_state(philo, mode);
	philo->eat_n++;
	pthread_mutex_lock(&philo->ptr_main->mx_phlio_state);
	philo->last_eat_time = philo->ptr_main->state.time;
	pthread_mutex_unlock(&philo->ptr_main->mx_phlio_state);
	usleep(philo->ptr_main->info->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->ptr_main->forks[first_fork]);
	pthread_mutex_unlock(&philo->ptr_main->forks[second_fork]);

}

static void ig_sleep(t_philo *philo, enum e_philo_state mode)
{
	ig_state(philo, mode);
	pthread_mutex_lock(&philo->ptr_main->mx_phlio_state);
	philo->eat_n++;
	pthread_mutex_unlock(&philo->ptr_main->mx_phlio_state);
	if(philo->ptr_main->info->time_to_sleep)
		usleep(philo->ptr_main->info->time_to_sleep * 1000);
}

void ig_creat_thread(t_main *main)
{
	t_philo *philo;
	int 	i;

	i = 0;
	while (i < main->info->nu_philos)
	{
		philo = &main->philo[i];
		pthread_create(&philo->pthread, NULL, ig_philo_thread, (void *)philo);
		i++;
	}

}