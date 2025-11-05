#include "philo.h"

void	start(t_table *table)
{
	int	i;

	table->start_time = get_time_ms();
	i = 0;
	while (i < table->n_philo)
	{
		init_philo(table, &table->philos[i], i + 1);
		i++;
	}
	pthread_create(&table->monitor, NULL, start_monitor, table);
}

void	*start_philo(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	while (!should_stop(philo) && !global_should_stop(philo->table))
	{
		philo_eat(philo);
		if (should_stop(philo) || global_should_stop(philo->table))
			break;
		philo_sleep(philo);
		if (should_stop(philo) || global_should_stop(philo->table))
			break;
		philo_think(philo);
	}
	return NULL;
}

void	*start_monitor(void *arg)
{
	t_table *table;
	int	i;

	table = (t_table *)arg;
	while (!global_should_stop(table))
	{
		i = 0;
		while (i < table->n_philo)
		{
			pthread_mutex_lock(&table->death_lock);
			if (philo_died(&table->philos[i]))
			{
				pthread_mutex_lock(&table->shared_stop_lock);
				table->shared_stop = 1;
				pthread_mutex_unlock(&table->shared_stop_lock);
				write_message(&table->philos[i], "died");
				return (pthread_mutex_unlock(&table->death_lock), NULL);
			}
			if (philo_is_full(&table->philos[i]))
			{
				pthread_mutex_lock(&table->philos[i].stop_lock);
				table->philos[i].stop_flag = 1;
				pthread_mutex_unlock(&table->philos[i].stop_lock);
			}
			pthread_mutex_unlock(&table->death_lock);
			i++;
		}
		smart_sleep(table, 1);
	}
	return NULL;
}