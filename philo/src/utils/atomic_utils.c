#include "philo.h"

// Fast path
int	should_stop(t_philo *philo)
{
	int	stop;
	pthread_mutex_lock(&philo->stop_lock);
	stop = philo->stop_flag;
	pthread_mutex_unlock(&philo->stop_lock);
	return (stop);
}

// Slow path
int global_should_stop(t_table *table)
{
	int stop;
	pthread_mutex_lock(&table->shared_stop_lock);
	stop = table->shared_stop;
	pthread_mutex_unlock(&table->shared_stop_lock);
	return (stop);
}

void	set_global_stop(t_table *table)
{
	pthread_mutex_lock(&table->shared_stop_lock);
	table->shared_stop = 1;
	pthread_mutex_unlock(&table->shared_stop_lock);
}

// Atomic printf to stdout
void	print_message(t_philo *philo, char *msg)
{
	long long	timestamp;

	if (should_stop(philo) || global_should_stop(philo->table))
		return;
	timestamp = get_time_ms() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->write_lock);
	printf("%lld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->table->write_lock);
}

// Atomic printf to stdout exclusive to monitor (bypass simulation ended check)
void	write_message(t_philo *philo, char *msg)
{
	long long	timestamp;

	timestamp = get_time_ms() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->write_lock);
	printf("%lld %d %s\n", timestamp, philo->id, msg);
	pthread_mutex_unlock(&philo->table->write_lock);
}
