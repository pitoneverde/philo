#include "philo.h"

void	print_error_and_exit(char *msg)
{
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	philo_eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	if (table->n_philo == 1)
	{
		print_message(philo, "has taken a fork");
		smart_sleep(table, table->t_die);
		print_message(philo, "died");
		set_global_stop(table);
		return;
	}
	pick_forks(philo);
	pthread_mutex_lock(&philo->meal_lock);
	philo->times_eat++;
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	print_message(philo, "is eating");
	smart_sleep(table, table->t_eat);
	put_forks(philo);
}


void	philo_sleep(t_philo *philo)
{
	print_message(philo, "is sleeping");
	smart_sleep(philo->table, philo->table->t_sleep);
}

// Random small time for pseudo-randomizing order
void	philo_think(t_philo *philo)
{
	long long t;

	t = 1 + (philo->id * 3) % 10;
	print_message(philo, "is thinking");
	smart_sleep(philo->table, t);
}