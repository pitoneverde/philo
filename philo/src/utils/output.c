#include "philo.h"

void	print_error_and_exit(t_table *table, char *msg)
{
	cleanup(table);
	printf("%s\n", msg);
	exit(EXIT_FAILURE);
}

void	philo_eat(t_philo *philo)
{
	//Lock forks
	print_message(philo, "is eating");
	pthread_mutex_lock(&philo->meal_lock);
	philo->times_eat++;
	philo->last_meal = get_time_ms();
	pthread_mutex_unlock(&philo->meal_lock);
	smart_sleep(philo->table, philo->table->t_eat);
	//Unlock forks
}


void	philo_sleep(t_philo *philo)
{
	print_message(philo, "is sleeping");
	smart_sleep(philo->table, philo->table->t_sleep);
}

void	philo_think(t_philo *philo)
{
	long long t = 1 + (philo->id * 3) % 10;
	print_message(philo, "is thinking");
	smart_sleep(philo->table, t);
}