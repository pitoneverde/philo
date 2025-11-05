#include "philo.h"

void	*start_philo(void *arg)
{
	
}
/*
void *philosopher_routine(void *arg)
{
    t_philo *philo = (t_philo *)arg;
    
    while (!should_stop(philo) && !global_should_stop(philo->table))
    {
        // Philosopher activities (eat, sleep, think)
        if (eat(philo) != 0)
            break;
        if (should_stop(philo) || global_should_stop(philo->table))
            break;
            
        if (philo_sleep(philo) != 0)
            break;
        if (should_stop(philo) || global_should_stop(philo->table))
            break;
            
        if (think(philo) != 0)
            break;
    }
    return NULL;
}

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

// Fast path - check local first
int should_stop(t_philo *philo) {
    pthread_mutex_lock(&philo->stop_lock);
    int stop = philo->stop;
    pthread_mutex_unlock(&philo->stop_lock);
    return stop;
}

// Slower path - check global only if needed  
int global_should_stop(t_table *table) {
    pthread_mutex_lock(&table->stop_lock);
    int stop = table->global_stop;
    pthread_mutex_unlock(&table->stop_lock);
    return stop;
}
*/