#include "philo.h"

static void signal_and_terminate_philos(t_table *table);
static void destroy_mutexes(t_table *table);

void	cleanup(t_table *table)
{
	int i;
	
	pthread_mutex_lock(&table->shared_stop_lock);
	table->shared_stop = 1;
	pthread_mutex_unlock(&table->shared_stop_lock);
	signal_and_terminate_philos(table);
	pthread_join(table->monitor, NULL);
	destroy_mutexes(table);
	if (table->philos)
		free(table->philos);
	if	(table->forks)
		free(table->forks);
}

// Separate signaling and joining to avoid deadlocks
static void signal_and_terminate_philos(t_table *table)
{
	int	i;

	if (table->philos)
	{
		i = 0;
		while (i < table->n_philo)
		{
			pthread_mutex_lock(&table->philos[i].stop_lock);
			table->philos[i].stop_flag = 1;
			pthread_mutex_unlock(&table->philos[i++].stop_lock);
		}
		i = 0;
		while (i < table->n_philo)
			pthread_join(table->philos[i++].thread, NULL);
	}
}

static void destroy_mutexes(t_table *table)
{
	int	i;

	pthread_mutex_destroy(&table->death_lock);
	pthread_mutex_destroy(&table->write_lock);
	pthread_mutex_destroy(&table->shared_stop_lock);
	i = 0;
	if (table->forks)
		while (i < table->n_philo)
			pthread_mutex_destroy(&table->forks[i++]);
	i = 0;
	if (table->philos)
		while (i < table->n_philo)
		{
			pthread_mutex_destroy(&table->philos[i].meal_lock);
			pthread_mutex_destroy(&table->philos[i++].stop_lock);
		}
}