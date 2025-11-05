#include "philo.h"

int	philo_died(t_philo *philo)
{
	long long elapsed;

	pthread_mutex_lock(&philo->meal_lock);
	elapsed = get_time_ms() - philo->last_meal;
	pthread_mutex_unlock(&philo->meal_lock);
	if (elapsed > philo->table->t_die)
		return (1);
	return (0);
}

//TODO: let the sim end if all threads are stopped
int philo_is_full(t_philo *philo)
{
	int	times_eaten;

	pthread_mutex_lock(&philo->meal_lock);
	times_eaten = philo->times_eat;
	pthread_mutex_unlock(&philo->meal_lock);
	if (times_eaten == philo->table->times_eat)
		return (1);
	return (0);
}