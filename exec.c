
#include "philo.h"

static void ig_eat(t_thread *dinner, enum e_philo_state mode);
static void ig_sleep(t_thread *dinner, enum e_philo_state mode);

void *ig_philo_thread(void *param)
{
	t_thread *dinner;

	dinner = (t_thread *)param;
	while(!ig_check_thread(dinner, 0))
	{
		ig_state(dinner, THINKING);
		ig_eat(dinner, EATING);
		ig_sleep(dinner, SLEEPING);
	}
	free(dinner);
	exit(0);
}

static void ig_eat(t_thread *dinner, enum e_philo_state mode)
{
	int right_fork;
	int left_fork;

	right_fork = dinner->dinning.philo->id;
	left_fork = dinner->dinning.philo->id + 1;
	if(dinner->dinning.philo->id % 2 == 0)
	{
		pthread_mutex_lock(&dinner->dinning.forks[right_fork]);
		ig_state(dinner, HAS_FORK);
	}
	ig_check_forks(dinner, right_fork, 0);
	pthread_mutex_lock(&dinner->dinning.forks[left_fork]);
	if(dinner->dinning.philo->id % 2 == 1)
		pthread_mutex_lock(&dinner->dinning.forks[right_fork]);
	ig_check_forks(dinner,right_fork, left_fork);
	ig_state(dinner, HAS_FORK);
	ig_check_forks(dinner, right_fork, left_fork);
	ig_state(dinner, mode);
	pthread_mutex_lock(&dinner->dinning.mx_phlio_state);
	dinner->dinning.philo[dinner->i].last_eat_time =
			dinner->dinning.philo[dinner->i].state.time;
	pthread_mutex_unlock(&dinner->dinning.mx_phlio_state);
	usleep(dinner->dinning.info->time_to_eat * 1000);
	pthread_mutex_unlock(&dinner->dinning.forks[right_fork]);
	pthread_mutex_unlock(&dinner->dinning.forks[left_fork]);
}

static void ig_sleep(t_thread *dinner, enum e_philo_state mode)
{
	ig_state(dinner, mode);
	pthread_mutex_lock(&dinner->dinning.mx_phlio_state);
	dinner->dinning.philo[dinner->i].eat_n++;
	pthread_mutex_unlock(&dinner->dinning.mx_phlio_state);
	if(dinner->dinning.info->time_to_sleep)
		usleep(dinner->dinning.info->time_to_sleep * 1000);
}