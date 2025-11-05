#include "philo.h"

int		main(int ac, char **av)
{
	t_table table;
	if (ac != 5 && ac != 6)
		print_error_and_exit(&table, "Argument count must be 5 or 6");
	parse_args(&table, ac, av);
	init(&table);
	start(&table);
	while (!global_should_stop(&table))
		smart_sleep(&table, 1);
	cleanup(&table);
	return 0;
}

void	start(t_table *table)
{
	int	i;
	table->start_time = get_time_ms();
	i = 0;
	while (i < table->n_philo)
	{
		init_philo(table, &table->philos[i], i + 1);
		i++;
	}
}