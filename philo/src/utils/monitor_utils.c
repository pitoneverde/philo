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

int	should_simulation_end(t_table *table,
	unsigned int *i, unsigned int *count_full)
{
	pthread_mutex_lock(&table->death_lock);
	if (philo_died(&table->philos[*i]))
	{
		set_global_stop(table);
		write_message(&table->philos[*i], "died");
		return (pthread_mutex_unlock(&table->death_lock), 1);
	}
	if (philo_is_full(&table->philos[*i]))
	{
		(*count_full)++;
		if (*count_full == table->n_philo)
		{
			set_global_stop(table);
			return (pthread_mutex_unlock(&table->death_lock), 1);
		}	
		pthread_mutex_lock(&table->philos[*i].stop_lock);
		table->philos[*i].stop_flag = 1;
		pthread_mutex_unlock(&table->philos[*i].stop_lock);
	}
	pthread_mutex_unlock(&table->death_lock);
	return (0);
}