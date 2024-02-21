
#include "./philo.h"

t_main *ig_init_dinner(int argc, char **args)
{
	t_main  *dining_philos;

	dining_philos = (t_main*)malloc(sizeof(t_main));
	dining_philos->info = (t_inf*)malloc(sizeof(t_inf));
	dining_philos->info->nu_philos = ig_atoi(args[1]);
	dining_philos->info->time_to_die = ig_atoi(args[2]);
	dining_philos->info->time_to_eat = ig_atoi(args[3]);
	dining_philos->info->time_to_sleep = ig_atoi(args[4]);
	dining_philos->info->each_philos_eat = -1;
	if (argc == 6)
		dining_philos->info->each_philos_eat = ig_atoi(args[5]);
	dining_philos->dead_philo = 0;
	dining_philos->philo = (t_philo *)malloc(ig_atoi(args[1]) * sizeof(t_philo));
	dining_philos->forks = malloc(ig_atoi(args[1]) * sizeof(pthread_mutex_t));
	pthread_mutex_init(&dining_philos->mx_each_ate_enough, NULL);
	pthread_mutex_init(&dining_philos->mx_phlio_state, NULL);
	pthread_mutex_init(&dining_philos->mx_dead_philo, NULL);
	pthread_mutex_init(&dining_philos->mx_print, NULL);
	return (dining_philos);
}

int ig_atoi(const char *string)
{
	int numb;
	int     neg;

	numb = 0;
	neg = 1;
	while ((*string >= 9 && *string <= 13) || *string == 32)
		string++;
	if (*string == '+' || *string == '-')
			if (*string++ == '-')
				neg = -1;
	while (*string >= '0' && *string <='9')
		numb = (numb * 10) + ((*string++) - 48);
	return (numb * neg);
}

t_thread	*ig_init_thread_table(t_main *dining)
{
	t_thread *tmp;

	tmp = malloc(sizeof(*tmp));
	tmp->i = -1;
	tmp->dinning = *dining;
	return (tmp);
}

void ig_threads(t_main *dinner)
{
	int	 i;
	t_thread	*dinning;

	i = 0;
	while (i < dinner->info->nu_philos)
	{
		dinning = (t_thread *)malloc(sizeof(t_thread));
		dinning->i = i;
		dinning->dinning.philo[i].id = i;
		pthread_create(dinner->philo[i].pthread, NULL, ig_philo_thread,
					   (void *)dinning);
		i++;
	}
}