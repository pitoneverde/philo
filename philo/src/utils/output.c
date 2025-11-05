#include "philo.h"

void	print_error_and_exit(t_table *table, char *msg)
{
	cleanup(table);
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	print_message(t_table *table, char *msg)
{
	pthread_mutex_lock(&table->write_lock);
	printf("%ll", get_time_ms());
	printf("%s\n", msg);
	pthread_mutex_unlock(&table->write_lock);
}