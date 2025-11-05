#include "philo.h"

void	init(t_table *table)
{
	int	i;

	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->death_lock, NULL);
	pthread_mutex_init(&table->shared_stop_lock, NULL);
	table->philos = malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philos)
		print_error_and_exit(&table, "Malloc failed @philos");
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!table->forks)
		print_error_and_exit(&table, "Malloc failed @forks");
	i = 0;
	while (i < table->n_philo)
		pthread_mutex_init(&table->forks[i++], NULL);
}

void	init_philo(t_table *table, t_philo *philo, int id)
{
	philo->stop_flag = 0;
	philo->id = id;
	philo->times_eat = 0;
	philo->table = table;
	pthread_mutex_init(&philo->meal_lock, NULL);
	pthread_mutex_init(&philo->stop_lock, NULL);
	philo->last_meal = table->start_time;
	philo->left = 0;
	philo->right = 0;
	pthread_create(&philo->thread, NULL, start_philo, NULL);
}