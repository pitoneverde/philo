#include "philo.h"

void	pick_forks(t_philo *philo)
{
	if (philo->left < philo->right)
	{
		pthread_mutex_lock(&philo->table->forks[philo->left]);
		pthread_mutex_lock(&philo->table->forks[philo->right]);
	}
	else
	{
		pthread_mutex_lock(&philo->table->forks[philo->right]);
		pthread_mutex_lock(&philo->table->forks[philo->left]);
	}
}

void	put_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->table->forks[philo->left]);
	pthread_mutex_unlock(&philo->table->forks[philo->right]);
}