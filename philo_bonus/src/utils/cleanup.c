#include "bonus_philo.h"

void	free_table_data(t_table *table)
{
	if (table->forks_sem != NULL && table->forks_sem != SEM_FAILED)
		sem_close(table->forks_sem);
	if (table->stop_mutex != NULL && table->stop_mutex != SEM_FAILED)
		sem_close(table->stop_mutex);
	if (table->stop_sem != NULL && table->stop_sem != SEM_FAILED)
		sem_close(table->stop_sem);
	if (table->stdout_sem != NULL && table->stdout_sem != SEM_FAILED)
		sem_close(table->stdout_sem);
}

// sem_unlink does nothing if the sem doesn't exist
void	cleanup(t_table *table)
{
	int	i;
	if (table)
	{
		free_table_data(table);
		sem_unlink(STDOUT_SEM_NAME);
		sem_unlink(FORKS_SEM_NAME);
		sem_unlink(STOP_MUTEX_NAME);
		sem_unlink(STOP_SEM_NAME);
		i = 0;
		while (i < table->n_philo)
		{
			sem_unlink(table->philos[i].death_name);
			sem_unlink(table->philos[i++].meal_name);
		}
		if (table->children_pid)
			free(table->children_pid);
		if (table->philos)
			free(table->philos);
	}
}

// Should free also the table heap fields,
// not in the same address space due to COW
void cleanup_philo(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (philo->death_mutex != NULL && philo->death_mutex != SEM_FAILED)
		sem_close(philo->death_mutex);
	if (philo->meal_mutex != NULL && philo->meal_mutex != SEM_FAILED)
		sem_close(philo->meal_mutex);
	// if (philo->stop_mutex != NULL && philo->stop_mutex != SEM_FAILED)
	// 	sem_close(philo->stop_mutex);
	if (table)
	{
		free_table_data(table);
		if (table->children_pid)
			free(table->children_pid);
		if (table->philos)
			free(table->philos);
	}
}