/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:06:43 by sabruma           #+#    #+#             */
/*   Updated: 2025/11/10 19:30:13 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init(t_table *table)
{
	unsigned int	i;

	table->philos = NULL;
	table->forks = NULL;
	table->shared_stop = 0;
	if (pthread_mutex_init(&table->write_lock, NULL) != 0)
		print_error_and_exit("Mutex init failed @write_lock");
	if (pthread_mutex_init(&table->death_lock, NULL) != 0)
		print_error_and_exit("Mutex init failed @death_lock");
	if (pthread_mutex_init(&table->shared_stop_lock, NULL) != 0)
		print_error_and_exit("Mutex init failed @shared_stop_lock");
	table->philos = malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philos)
		print_error_and_exit("Malloc failed @philos");
	table->forks = malloc(sizeof(pthread_mutex_t) * table->n_philo);
	if (!table->forks)
		print_error_and_exit("Malloc failed @forks");
	i = 0;
	while (i < table->n_philo)
		if (pthread_mutex_init(&table->forks[i++], NULL) != 0)
			print_error_and_exit("Mutex init failed @forks");
}

void	init_philo(t_table *table, t_philo *philo, int id)
{
	philo->stop_flag = 0;
	philo->id = id;
	philo->times_eat = 0;
	philo->table = table;
	if (pthread_mutex_init(&philo->meal_lock, NULL) != 0)
		print_error_and_exit("Mutex init failed @meal_lock");
	if (pthread_mutex_init(&philo->stop_lock, NULL) != 0)
		print_error_and_exit("Mutex init failed @stop_lock");
	philo->last_meal = table->start_time;
	philo->left = id - 1;
	philo->right = (id) % table->n_philo;
	if (pthread_create(&philo->thread, NULL, start_philo, philo) != 0)
		print_error_and_exit("Pthread create failed @philo");
}
