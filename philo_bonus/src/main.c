#include "bonus_philo.h"
#include <string.h>
#include <sys/time.h>

int	main(int ac, char **av)
{
	t_table table;
	if (ac != 5 && ac != 6)
		print_error_and_exit("Invalid argument count");
	memset(&table, 0, sizeof(t_table));
	parse_args(&table, ac, av);
	init(&table);
	start(&table);
	wait_for_end(&table);	// waits for all children termination or signal flag for termination set
	cleanup(&table);
}