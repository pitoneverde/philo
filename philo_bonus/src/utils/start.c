# include "bonus_philo.h"

void	start(t_table *table)
{
	int		i;
	pid_t	pid;
	t_philo	philo;

	i = 0;
	while (i < table->n_philo)
	{
		pid = fork();
		if (pid == 0)
			start_philo(&philo, i);
		else
			table->children_pid[i] = pid;
		i++;
	}
}

void	start_philo(t_philo *philo, int id)
{
	init_philo(philo->table, philo, id);
	pthread_detach(philo->death_thread);
	pthread_join(philo->life_thread, NULL);
	sem_close(philo->sem_name);
	sem_unlink(philo->sem_name);
	exit(0);
}

// regular thread
void *philo_life(void *arg)
{
	return NULL;
}

// monitor thread: if it detects a death, signals main and exits
void *philo_death(void *arg)
{
	return NULL;
}