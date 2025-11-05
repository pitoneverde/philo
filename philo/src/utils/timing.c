#include "philo.h"

long long	get_time_ms()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (long long)(t.tv_sec * 1000 + t.tv_usec / 1000);
}

// This function can be preempted with table->shared_stop flag set
void smart_sleep(t_table *table, long long ms)
{
	long long	time_start;

	time_start = get_time_ms();
	while ((get_time_ms() - time_start) < ms)
	{
		// if (global_should_stop(table)) break;
		// if (table->shared_stop)
//			break;
		usleep(500);
	}
}