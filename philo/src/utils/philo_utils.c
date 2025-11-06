#include "philo.h"

// Can't pick up same forks
void	pick_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(&philo->table->forks[philo->left]);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->right]);
		print_message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[philo->right]);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->table->forks[philo->left]);
		print_message(philo, "has taken a fork");
	}
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->left]);
	pthread_mutex_unlock(&philo->table->forks[philo->right]);
}