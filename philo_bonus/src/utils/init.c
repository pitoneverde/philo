#include "bonus_philo.h"
#include <fcntl.h>
#include <string.h>

// TODO init_sem (sem_t *sem, char *name, int value) to reduce line count
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
		sem_unlink(STDOUT_SEM_NAME);
		table->stdout_sem = sem_open(STDOUT_SEM_NAME, O_CREAT, 0644, 1);
	}
	table->stop_sem = sem_open(STOP_SEM_NAME, O_CREAT | O_EXCL, 0644, 0);
	if (table->stop_sem == SEM_FAILED)
	{
		sem_unlink(STOP_SEM_NAME);
		table->stop_sem = sem_open(STOP_SEM_NAME, O_CREAT, 0644, 0);
	}
	table->stop_mutex = sem_open(STOP_MUTEX_NAME, O_CREAT | O_EXCL, 0644, 1);
	if (table->stop_mutex == SEM_FAILED)
	{
		sem_unlink(STOP_MUTEX_NAME);
		table->stop_mutex = sem_open(STOP_MUTEX_NAME, O_CREAT, 0644, 1);
	}
	table->shared_stop_flag = 0;
	table->start_timestamp = get_time_ms();
}

// Reopens stop semaphores cause table is a copy, called after fork()
void	init_philo(t_table *table, t_philo *philo, int id)
{
	// philo->death_thread = 0;
	// philo->life_thread = 0;
	philo->id = id;
	philo->table = table;
	philo->last_meal = table->start_timestamp;
	// philo->meal_count = 0;
	philo->local_stop_flag = 0;
	set_sem_name(PHILO_DEATH_SEM_, philo->death_name, philo);
	philo->death_mutex = sem_open(philo->death_name, O_CREAT | O_EXCL, 0644, 1);
	if (philo->death_mutex == SEM_FAILED)
	{
		sem_unlink(philo->death_name);
		philo->death_mutex = sem_open(philo->death_name, O_CREAT, 0644, 1);
	}
	// set_sem_name(PHILO_STOP_MUTEX_, philo->stop_name, philo);
	// philo->stop_mutex = sem_open(philo->stop_name, O_CREAT | O_EXCL, 0644, 1);
	// if (philo->stop_mutex == SEM_FAILED)
	// {
	// 	sem_unlink(philo->stop_name);
	// 	philo->stop_mutex = sem_open(philo->stop_name, O_CREAT, 0644, 1);
	// }
	set_sem_name(PHILO_MEAL_MUTEX_, philo->meal_name, philo);
	philo->meal_mutex = sem_open(philo->meal_name, O_CREAT | O_EXCL, 0644, 1);
	if (philo->meal_mutex == SEM_FAILED)
	{
		sem_unlink(philo->meal_name);
		philo->meal_mutex = sem_open(philo->meal_name, O_CREAT, 0644, 1);
	}
	table->stop_sem = sem_open(STOP_SEM_NAME, 0);
	table->stop_mutex = sem_open(STOP_MUTEX_NAME, 0);
	if (pthread_create(&philo->life_thread, NULL, philo_life, philo) != 0)
		print_error_and_exit("Pthread create life failed @init_philo");
	if (pthread_create(&philo->death_thread, NULL, philo_death, philo) != 0)
		print_error_and_exit("Pthread create death failed @init_philo");
}

// Unique id: PHILO_DEATH_SEM_PREFIX + table->start_timestamp + philo->id
void	set_sem_name(char *prefix, char *sem_name, t_philo *philo)
{
	char	*str_id;
	char	*timestamp;

	memset(sem_name, 0, 50);
	strcat(sem_name, prefix);
	timestamp = lltoa(philo->table->start_timestamp);
	strcat(sem_name, timestamp);
	strcat(sem_name, "_");
	str_id = utoa(philo->id);
	strcat(sem_name, str_id);
	free(timestamp);
	free(str_id);
}