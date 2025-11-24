#include "bonus_philo.h"
#include <sys/time.h>

long long	get_time_ms(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((long long)(t.tv_sec * 1000 + t.tv_usec / 1000));
}