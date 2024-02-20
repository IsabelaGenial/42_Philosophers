
#include "philo.h"

static void ig_eat(t_thread *dinner);

void *ig_philo_thread(void *param)
{
	t_thread *dinner;

	dinner = (t_thread *)param;
	while(!ig_check_thread(dinner, 0))
		ig_eat(dinner);
	exit(0);
}

static void ig_eat(t_thread *dinner)
{
	int right_fork;
	int left_fork;

	right_fork = dinner->dinning.philo->id;
	left_fork = dinner->dinning.philo->id + 1;
	if(dinner->dinning.philo->id % 2 == 0)
		pthread_mutex_lock(&dinner->dinning.forks[right_fork]);
	pthread_mutex_lock(&dinner->dinning.forks[left_fork]);
	if(dinner->dinning.philo->id % 2 == 1)
		pthread_mutex_lock(&dinner->dinning.forks[right_fork]);
}