#include "bonus_philo.h"
#include <fcntl.h>

void	init(t_table *table)
{
	table->forks_sem = sem_open(FORKS_SEM_NAME, O_CREAT | O_EXCL, 0644, table->n_philo);
	table->stdout_sem = sem_open(STDOUT_SEM_NAME, O_CREAT | O_EXCL, 0644, 1);
	table->children_pid = malloc(sizeof(pid_t) * table->n_philo);
	if (!table->children_pid)
		print_error_and_exit("Malloc failed @children_pid");
	table->start_timestamp = get_time_ms();
}

void	init_philo(t_table *table, t_philo *philo, int id)
{
	philo->id = id;
	philo->table = table;
	philo->last_meal = table->start_timestamp;
	philo->sem_name = get_sem_name(philo);
	philo->death_sem = sem_open(philo->sem_name, O_CREAT | O_EXCL, 0644, 1);
	pthread_create(&philo->life_thread, NULL, philo_life, philo);
	pthread_create(&philo->death_thread, NULL, philo_death, philo);
}

char	*get_sem_name(t_philo *philo)
{
	char	*str_id;
	char	*timestamp;
	char	name[50];

	strcat(name, PHILO_SEM_PREFIX);
	strcat(name, "_");
	timestamp = lltoa(philo->table->start_timestamp);
	strcat(name, timestamp);
	strcat(name, "_");
	str_id = utoa(philo->id);
	strcat(name, str_id);
	return (name);
}