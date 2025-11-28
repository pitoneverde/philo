#include "bonus_philo.h"

int	philo_should_stop(t_philo *philo)
{
	int	stop;

	sem_wait(philo->death_mutex);
	stop = philo->local_stop_flag;
	sem_post(philo->death_mutex);
	return (stop);
}

void set_local_stop(t_philo *philo)
{
	sem_wait(philo->death_mutex);
	philo->local_stop_flag = 1;
	sem_post(philo->death_mutex);
}

void die(t_philo *philo)
{
	sem_wait(philo->death_mutex);
	philo->local_stop_flag = 1;
	philo->exit_status = EXIT_DEATH;
	sem_post(philo->death_mutex);
}