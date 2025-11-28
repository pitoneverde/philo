#include "bonus_philo.h"

void print_error_and_exit(char *err)
{
	printf("%s\n", err);
	exit(EXIT_ERROR);
}

// Atomic printf
void	print_message(t_philo *philo, char *msg)
{
	t_table		*table;
	long long	timestamp;

	table = philo->table;
	timestamp = get_time_ms() - table->start_timestamp;
	sem_wait(table->stdout_sem);
	printf("%07lld %d %s\n", timestamp, philo->id, msg);
	sem_post(table->stdout_sem);
}