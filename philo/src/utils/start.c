/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:07:00 by sabruma           #+#    #+#             */
/*   Updated: 2025/11/10 19:31:31 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start(t_table *table)
{
	unsigned int	i;

	if (table->n_philo == 0)
		return (set_global_stop(table));
	table->start_time = get_time_ms();
	i = 0;
	while (i < table->n_philo)
	{
		init_philo(table, &table->philos[i], i + 1);
		i++;
	}
	if (pthread_create(&table->monitor, NULL, start_monitor, table) != 0)
		print_error_and_exit("Pthread create failed @monitor");
}

void	*start_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!should_stop(philo) && !global_should_stop(philo->table))
	{
		philo_eat(philo);
		if (should_stop(philo) || global_should_stop(philo->table))
			break ;
		philo_sleep(philo);
		if (should_stop(philo) || global_should_stop(philo->table))
			break ;
		philo_think(philo);
	}
	return (NULL);
}

void	*start_monitor(void *arg)
{
	t_table			*table;
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
