#include "philo.h"

void	print_error_and_exit(t_table *table, char *msg)
{
	cleanup(table);
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}
