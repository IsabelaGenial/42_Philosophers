
#include "philo.h"

void ig_threads(t_main *dinner)
{
	int	 i;
	t_thread	*dinning;

	i = 0;
	while (i < dinner->info->nu_philos)
	{
		dinning = (t_thread *)malloc(sizeof(t_thread));
		dinning->i = i;
		dinner->philo[i]->id = i;
		pthread_create(dinner->philo[i].pthread, NULL, )
	}
}

void *routine_philo(void *arg)
{
	t_thread *dinning;

	dinning = arg;
	while()
	{

	}
}

int eat(t_thread *table)
{
	int right_fork;
	int left_fork;

	
}