#include "philo.h"

long long	get_time_ms()
{
	struct timeval t;
	gettimeofday(&t, NULL);
	return (long long)(t.tv_sec * 1000 + t.tv_usec / 1000);
}

void smart_sleep(long long ms)
{
	long long	time_start;

	time_start = get_time_ms();
	while ((get_time_ms() - time_start) < ms)
		usleep(500);
}