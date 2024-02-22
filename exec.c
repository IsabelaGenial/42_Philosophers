
#include "philo.h"

static void ig_eat(t_philo *philo, enum e_philo_state mode);
static void ig_sleep(t_philo *philo, enum e_philo_state mode);

void *ig_philo_thread(void *param)
{
	t_philo *philo;

	philo = (t_philo *)param;
	while(!ig_check_thread(philo->ptr_main, 0))
	{
		ig_state(philo, THINKING);
		ig_eat(philo, EATING);
		ig_sleep(philo, SLEEPING);
	}
	exit(0);
}

static void ig_eat(t_philo *philo, enum e_philo_state mode)
{
	int right_fork;
	int left_fork;

	right_fork = philo->id;
	left_fork = philo->id - 1;
	if(philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->ptr_main->forks[right_fork]);
		ig_state(philo, HAS_FORK);
	}
	ig_check_forks(philo->ptr_main, right_fork, 0);
	pthread_mutex_lock(&philo->ptr_main->forks[left_fork]);
	if(philo->id % 2 == 1)
		pthread_mutex_lock(&philo->ptr_main->forks[right_fork]);
	ig_check_forks(philo->ptr_main,right_fork, left_fork);
	ig_state(philo, HAS_FORK);
	ig_check_forks(philo->ptr_main, right_fork, left_fork);
	ig_state(philo, mode);
	pthread_mutex_lock(&philo->ptr_main->mx_phlio_state);
	philo->last_eat_time = philo->ptr_main->state.time;
	pthread_mutex_unlock(&philo->ptr_main->mx_phlio_state);
	usleep(philo->ptr_main->info->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->ptr_main->forks[right_fork]);
	pthread_mutex_unlock(&philo->ptr_main->forks[left_fork]);
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