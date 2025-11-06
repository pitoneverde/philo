#include "philo.h"

void	start(t_table *table)
{
	unsigned int	i;

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
	t_table 		*table;
	unsigned int	i;
	unsigned int	count_full;

	table = (t_table *)arg;
	while (!global_should_stop(table))
	{
		count_full = 0;
		i = 0;
		while (i < table->n_philo)
		{
			if (should_simulation_end(table, &i, &count_full))
				return (NULL);
			i++;
		}
		smart_sleep(table, 1);
	}
	return (NULL);
}