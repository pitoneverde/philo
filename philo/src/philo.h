#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct s_table
{
	unsigned int    n_philo;
	unsigned int    t_die;
	unsigned int    t_eat;
	unsigned int    t_sleep;
	int             times_eat;   // Optional (-1 = not set)

	pthread_mutex_t *forks;
	pthread_mutex_t write_lock;
	pthread_mutex_t death_lock;
	t_philo         *philos;
	long long       start_time;
}   t_table;

typedef struct s_philo
{
	int             id;
	int             times_eat;
	long long       last_meal;  // Read by monitor
	pthread_t		thread;
	pthread_mutex_t meal_lock;

	t_table         *table;
	int             left;
	int             right;
}   t_philo;

unsigned int	atou_safe(char *num);

void			parse_args(t_table *table, int ac, char **av);
void			smart_sleep(long long ms);
long long		get_time_ms();
void			print_error_and_exit(char *msg);

void			*start_philo(void *arg);
void			start(t_table *table);
void			init(t_table *table);
void			init_philo(t_table *table, t_philo *philo, int id);
