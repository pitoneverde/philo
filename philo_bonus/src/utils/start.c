# include "bonus_philo.h"

void	start(t_table *table)
{
	int		i;
	pid_t	pid;
	
	i = 0;
	while (i < table->n_philo)
	{
		pid = fork();
		if (pid == 0)
			start_philo(table, &table->philos[i], i);
		else
			table->children_pid[i] = pid;
		i++;
	}
}

void	start_philo(t_table *table, t_philo *philo, int id)
{
	init_philo(table, philo, id);
	cleanup_philo(philo);
	exit(EXIT_SUCCESS);
}

// regular thread
void *philo_life(void *arg)
{
	(void)arg;
	return NULL;
}

// monitor thread: if it detects a death, signals main and exits
void *philo_death(void *arg)
{
	(void)arg;
	return NULL;
}
