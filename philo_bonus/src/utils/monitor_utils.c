#include "bonus_philo.h"

int philo_died(t_philo *philo)
{
	long long	elapsed;

	sem_wait(philo->meal_mutex);
	elapsed = get_time_ms() - philo->last_meal;
	sem_post(philo->meal_mutex);
	if (elapsed > philo->table->t_die)
		return (1);
	return (0);
}