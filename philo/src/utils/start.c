#include "philo.h"

void	*start_philo(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	while (!should_stop(philo) && !global_should_stop(philo->table))
	{
		philo_eat(philo);
		if (should_stop(philo) || global_should_stop(philo->table))
			break;
		philo_sleep(philo);
		if (should_stop(philo) || global_should_stop(philo->table))
			break;
		philo_think(philo);
	}
	return NULL;
}

void	*start_monitor(void *arg)
{
	t_table *table = (t_philo *)arg;
	while (!global_should_stop(table))
	{

	}
}

/*
// In monitor thread - when a philosopher dies
void *monitor_routine(void *arg)
{
    t_table *table = (t_table *)arg;
    
    while (!global_should_stop(table))
    {
        for (int i = 0; i < table->num_philos; i++)
        {
            if (philosopher_died(&table->philos[i]))
            {
                // Set global stop - ALL philosophers should stop
                pthread_mutex_lock(&table->stop_lock);
                table->global_stop = 1;
                pthread_mutex_unlock(&table->stop_lock);
                
                print_death_message(&table->philos[i]);
                return NULL;
            }
        }
        usleep(1000); // Check every 1ms
    }
    return NULL;
}
*/