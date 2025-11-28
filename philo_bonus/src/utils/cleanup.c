#include "bonus_philo.h"

void	cleanup(t_table *table)
{
	int	i;
	if (table->n_philo > 0)
	{
		if (table->forks_sem != NULL && table->forks_sem != SEM_FAILED)
			sem_close(table->forks_sem);
		if (table->stdout_sem != NULL && table->stdout_sem != SEM_FAILED)
			sem_close(table->stdout_sem);
		sem_unlink(STDOUT_SEM_NAME);
		sem_unlink(FORKS_SEM_NAME);
		i = 0;
		while (i < table->n_philo)
			sem_unlink(table->philos[i++].sem_name);
	}
	if (table->children_pid)
		free(table->children_pid);
	if (table->philos)
		free(table->philos);
}

// Should free also the table heap fields, not in the same address space due to COW
void cleanup_philo(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (philo->death_thread)
		pthread_join(philo->death_thread, NULL);
	if (philo->life_thread)
		pthread_join(philo->life_thread, NULL);
	if (philo->death_sem != NULL && philo->death_sem != SEM_FAILED)
		sem_close(philo->death_sem);
	// sem_unlink(philo->sem_name);
	if (table)
	{
		if (table->children_pid)
			free(table->children_pid);
		if (table->philos)
			free(table->philos);
		if (table->forks_sem != NULL && table->forks_sem != SEM_FAILED)
			sem_close(table->forks_sem);
		if (table->stdout_sem != NULL && table->stdout_sem != SEM_FAILED)
			sem_close(table->stdout_sem);
	}
}