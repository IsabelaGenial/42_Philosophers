
#include "philo.h"

static void ig_eat(t_philo *philo, enum e_philo_state mode);
static void ig_sleep(t_philo *philo, enum e_philo_state mode);
void unlock_mutex(t_main *main);

void *ig_philo_thread(void *param)
{
	t_philo *philo;

	philo = (t_philo *)param;
	while(!ig_the_check(philo->ptr_main, 1))
	{
		ig_state(philo, THINKING);
		usleep(10);
		ig_eat(philo, EATING);
		ig_sleep(philo, SLEEPING);
	}
	return (0);
}

static void ig_eat(t_philo *philo, enum e_philo_state mode)
{
	int first_fork;
	int second_fork;

	if (philo->id % 2 == 0)
	{
		first_fork = philo->id;
		second_fork = philo->id - 1;
	}
	if (philo->id == 0)
		second_fork = philo->ptr_main->info->nu_philos - 1;
	else if (philo->id % 2 == 1)
	{
		first_fork = philo->id - 1;
		second_fork = philo->id;
		usleep(10);
	}
	ig_the_check(philo->ptr_main, 1);
	pthread_mutex_lock(&philo->ptr_main->forks[first_fork]);
	ig_state(philo, HAS_FORK);
	ig_check_forks(philo->ptr_main, first_fork, 0);
	pthread_mutex_lock(&philo->ptr_main->forks[second_fork]);
	ig_state(philo, HAS_FORK);
	ig_check_forks(philo->ptr_main, first_fork, second_fork);
	pthread_mutex_lock(&philo->ptr_main->mx_phlio_state);
	ig_state(philo, mode);
	philo->last_eat_time = get_time();
	pthread_mutex_unlock(&philo->ptr_main->mx_phlio_state);
	usleep(philo->ptr_main->info->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->ptr_main->forks[first_fork]);
	pthread_mutex_unlock(&philo->ptr_main->forks[second_fork]);
}

static void ig_sleep(t_philo *philo, enum e_philo_state mode)
{
	if (!ig_the_check(philo->ptr_main, 1))
	{
		ig_state(philo, mode);
		pthread_mutex_lock(&philo->ptr_main->mx_phlio_state);
		philo->eat_n++;
		pthread_mutex_unlock(&philo->ptr_main->mx_phlio_state);
		if (philo->ptr_main->info->time_to_sleep)
			usleep(philo->ptr_main->info->time_to_sleep * 1000);
	}
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

void *ig_mr_lonly(void *param)
{
	t_philo *philo;

	philo = (t_philo *)param;
	ig_state(philo, THINKING);
	usleep(100);
	pthread_mutex_lock(&philo->ptr_main->one_fork);
	pthread_mutex_unlock(&philo->ptr_main->one_fork);
	ig_state(philo, HAS_FORK);
	usleep(philo->ptr_main->info->time_to_die * 1000);
	ig_state(philo, DEAD);
	exit_thread(philo->ptr_main);
	exit(0);
}

void ig_creat_lonly(t_main *main)
{
	t_philo *philo;

	philo = &main->philo[0];
	pthread_create(&philo->pthread, NULL, ig_mr_lonly, (void *)philo);
	pthread_join(philo->pthread, NULL);
}

void exit_thread(t_main *main)
{
	int i;

	i=0;
	//unlock_mutex(main);
	pthread_mutex_destroy(&main->mx_phlio_state);
	pthread_mutex_destroy(&main->mx_each_ate_enough);
	pthread_mutex_destroy(&main->mx_dead_philo);
	while(i < main->info->nu_philos)
	{
		free(&main->forks[i]);
		i++;
	}
}

void unlock_mutex(t_main *main)
{
	pthread_mutex_unlock(&main->mx_each_ate_enough);
	pthread_mutex_unlock(&main->mx_phlio_state);
	pthread_mutex_unlock(&main->mx_state);
	pthread_mutex_unlock(&main->mx_dead_philo);
	pthread_mutex_unlock(&main->mx_print);
}