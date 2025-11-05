#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct s_table
{
	unsigned int	n_philo;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	int				times_eat;   // Optional (-1 = not set)
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	death_lock;
	t_philo			*philos;
	long long		start_time;
	int				shared_stop;
	pthread_mutex_t	shared_stop_lock;
}   t_table;

typedef struct s_philo
{
	int				id;
	int				times_eat;
	long long		last_meal;  // Read by monitor
	pthread_t		thread;
	pthread_mutex_t	meal_lock;
	t_table			*table;
	int				left;
	int				right;
	int				stop_flag;
	pthread_mutex_t	stop_lock;
}   t_philo;

void			smart_sleep(long long ms);
long long		get_time_ms(void);

void			*start_philo(void *arg)
				__attribute__((hot));

void			start(t_table *table);
void			init(t_table *table);
void			init_philo(t_table *table, t_philo *philo, int id);

void			parse_args(t_table *table, int ac, char **av)
				__attribute__((nonnull(1)));

void			print_error_and_exit(t_table *table, char *msg)
				__attribute__((noreturn));

unsigned int	atou_safe(char *num, int *check)
				__attribute__((nonnull(1, 2)))
				__attribute__((warn_unused_result));

void			cleanup(t_table *table)
				__attribute__((nonnull(1)));