#include "bonus_philo.h"
#include <fcntl.h>
#include <string.h>

void	init(t_table *table)
{
	table->philos = malloc(sizeof(t_philo) * table->n_philo);
	if (!table->philos)
		print_error_and_exit("Malloc failed @philos");
	memset(table->philos, 0, sizeof(t_philo) * table->n_philo);
	table->children_pid = malloc(sizeof(pid_t) * table->n_philo);
	if (!table->children_pid)
	{
		cleanup(table);
		print_error_and_exit("Malloc failed @children_pid");
	}
	memset(table->children_pid, 0, sizeof(pid_t) * table->n_philo);
	table->forks_sem = sem_open(FORKS_SEM_NAME, O_CREAT | O_EXCL, 0644, table->n_philo);
	if (table->forks_sem == SEM_FAILED)
	{
		sem_unlink(FORKS_SEM_NAME);
		table->forks_sem = sem_open(FORKS_SEM_NAME, O_CREAT, 0644, table->n_philo);
	}
	table->stdout_sem = sem_open(STDOUT_SEM_NAME, O_CREAT | O_EXCL, 0644, 1);
	if (table->stdout_sem == SEM_FAILED)
	{
		sem_unlink(FORKS_SEM_NAME);
		table->stdout_sem = sem_open(STDOUT_SEM_NAME, O_CREAT, 0644, 1);
	}
	table->start_timestamp = get_time_ms();
}

void	init_philo(t_table *table, t_philo *philo, int id)
{
	philo->death_thread = 0;
	philo->life_thread = 0;
	philo->death_sem = NULL;
	philo->id = id;
	philo->table = table;
	philo->last_meal = table->start_timestamp;
	set_sem_name(philo);
	philo->death_sem = sem_open(philo->sem_name, O_CREAT | O_EXCL, 0644, 1);
	if (philo->death_sem == SEM_FAILED)
	{
		sem_unlink(philo->sem_name);
		philo->death_sem = sem_open(philo->sem_name, O_CREAT, 0644, 1);
	}
	if (pthread_create(&philo->life_thread, NULL, philo_life, philo) != 0)
		print_error_and_exit("Pthread create life failed @init_philo");
	if (pthread_create(&philo->death_thread, NULL, philo_death, philo) != 0)
		print_error_and_exit("Pthread create death failed @init_philo");
}

// Unique id: PHILO_SEM_PREFIX + table->start_timestamp + philo->id
void	set_sem_name(t_philo *philo)
{
	char	*str_id;
	char	*timestamp;

	memset(philo->sem_name, 0, 50);
	strcat(philo->sem_name, PHILO_SEM_PREFIX);
	timestamp = lltoa(philo->table->start_timestamp);
	strcat(philo->sem_name, timestamp);
	strcat(philo->sem_name, "_");
	str_id = utoa(philo->id);
	strcat(philo->sem_name, str_id);
	free(timestamp);
	free(str_id);
}