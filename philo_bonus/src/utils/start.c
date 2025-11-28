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
			start_philo(table, &table->philos[i], i + 1);
		else
			table->children_pid[i] = pid;
		i++;
	}
}

void	start_philo(t_table *table, t_philo *philo, int id)
{
	int	exit_status;

	init_philo(table, philo, id);
	philo_loop(philo);
	pthread_join(philo->life_thread, NULL);
	pthread_join(philo->death_thread, NULL);
	sem_wait(philo->death_mutex);
	exit_status = philo->exit_status;
	sem_post(philo->death_mutex);
	cleanup_philo(philo);
	exit(exit_status);
}

// TODO: regular thread
// eat, sleep, think until it dies or another dies or eaten table->times_eat times or SIGTERM'ed
void *philo_life(void *arg)
{
	t_philo	*philo;
	int		meal_count;
	int		target;

	philo = (t_philo *)arg;
	meal_count = 0;
	target = philo->table->times_eat;
	while (!philo_should_stop(philo))
	{
		philo_eat(philo, &meal_count);
		if (target > 0 && meal_count >= target)
		{
			sem_wait(philo->death_mutex);
			philo->local_stop_flag = 1;
			philo->exit_status = EXIT_SUCCESS;
			sem_post(philo->death_mutex);
			break ;
		}
		if (philo_should_stop(philo))
			break ;
		philo_sleep(philo);
		if (philo_should_stop(philo))
			break ;
		philo_think(philo);
	}
	return (NULL);
}

// TODO: monitor thread: if it detects a death, signals main and exits
// if philo died --> exit(EXIT_DEATH) to signal death to main
// if philo->times_eat == table->times_eat --> both threads return and exit (EXIT_SUCCESS)
void *philo_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo_should_stop(philo))
	{
		if (philo_died(philo))
		{
			die(philo);
			print_message(philo, "died");
		}
		// if eaten enough times exit(EXIT_SUCCESS)
		smart_sleep(philo, 1);
	}
	return (NULL);
}

// Blocking wait for global or local stop signals
void philo_loop(t_philo *philo)
{
	int	should_stop;
	while (1)
	{
		sem_wait(philo->death_mutex);
		should_stop = philo->local_stop_flag;
		sem_post(philo->death_mutex);
		if (should_stop)
			break;
		sem_wait(philo->table->stop_sem);
		sem_wait(philo->death_mutex);
		philo->local_stop_flag = 1;
		sem_post(philo->death_mutex);
		sem_post(philo->table->stop_sem);
		break;
	}
}