#include "philo.h"

// number_of_philosophers
// time_to_die
// time_to_eat
// time_to_sleep
// [number_of_times_each_philosopher_must_eat]
void	parse_args(t_table *table, int ac, char **av)
{
	table->n_philo = atou_safe(av[1]); // should parse only positive nums
	table->t_die = atou_safe(av[2]);
	table->t_eat = atou_safe(av[3]);
	table->t_sleep = atou_safe(av[4]);
	if (ac == 6)
		table->times_eat = atou_safe(av[5]);
	else
		table->times_eat = -1;
}