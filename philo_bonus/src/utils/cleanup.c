#include "bonus_philo.h"

void	cleanup(t_table *table)
{
	if (table->n_philo > 0)
	{
		sem_close(table->stdout_sem);
		sem_close(table->forks_sem);
		sem_unlink(STDOUT_SEM_NAME);
		sem_unlink(FORKS_SEM_NAME);
	}
	if (table->children_pid)
		free(table->children_pid);
}