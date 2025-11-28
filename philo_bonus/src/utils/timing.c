#include "bonus_philo.h"
#include <sys/time.h>

long long	get_time_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((long long)(t.tv_sec * 1000 + t.tv_usec / 1000));
}
//TODO: smart_sleep with sems
// This function can be preempted with table->shared_stop flag set
void	smart_sleep(t_philo *philo, long long ms)
{
	long long	time_start;

	time_start = get_time_ms();
	while ((get_time_ms() - time_start) < ms)
	{
		if (philo_should_stop(philo))
			break ;
		usleep(500);
	}
}
