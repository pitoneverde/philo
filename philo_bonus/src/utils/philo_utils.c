//TODO: eat, sleep, think, pick forks
#include "bonus_philo.h"

void philo_eat(t_philo *philo, int *meal_count)
{
	// t_table	*table;

	// table = philo->table;
	// if (table->n_philo == 1)
	// {
	// 	print_message(philo, "has taken a fork");
	// 	smart_sleep(philo, table->t_die);
	// 	print_message(philo, "died");
	// 	set_local_stop(philo);
	// 	cleanup_philo(philo);
	// 	exit(EXIT_DEATH);
	// }
	pick_forks(philo);
	sem_wait(philo->meal_mutex);
	philo->last_meal = get_time_ms();
	(*meal_count)++;
	sem_post(philo->meal_mutex);
	print_message(philo, "is eating");
	smart_sleep(philo, philo->table->t_eat);
	put_forks(philo);
}

void philo_sleep(t_philo *philo)
{
	print_message(philo, "is sleeping");
	smart_sleep(philo, philo->table->t_sleep);
}

void philo_think(t_philo *philo)
{
	long long	t;

	t = 1 + (philo->id * 3) % 10;
	print_message(philo, "is thinking");
	smart_sleep(philo, t);
}

void pick_forks(t_philo *philo)
{
	sem_wait(philo->table->forks_sem);
	print_message(philo, "has taken a fork");
	sem_wait(philo->table->forks_sem);
	print_message(philo, "has taken a fork");
}

void put_forks(t_philo *philo)
{
	sem_post(philo->table->forks_sem);
	sem_post(philo->table->forks_sem);
}