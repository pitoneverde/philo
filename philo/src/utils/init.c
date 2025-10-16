#include "philo.h"

void	init(t_table *table)
{
	int	i;
	// table = malloc(sizeof(t_table));
	// if (!table)
	// 	print_error_and_exit("Malloc failed @table");
	pthread_mutex_init(&table->write_lock, NULL);
	pthread_mutex_init(&table->death_lock, NULL);
	table->philos = malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philos)
		print_error_and_exit("Malloc failed @philos");
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!table->forks)
		print_error_and_exit("Malloc failed @forks");
	i = 0;
	while (i < table->n_philo)
		pthread_mutex_init(&table->forks[i], NULL);
}

void	init_philo(t_table *table, t_philo *philo, int id)
{
	philo->id = id;
	philo->times_eat = 0;
	philo->table = table;
	pthread_mutex_init(&philo->meal_lock, NULL);
	philo->last_meal = table->start_time;
	philo->left = 0;
	philo->right = 0;
	pthread_create(&philo->thread, NULL, start_philo, NULL);
}