#ifndef BONUS_PHILO_H
# define BONUS_PHILO_H
# define FORKS_SEM_NAME "/philo_forks"
# define STDOUT_SEM_NAME "/philo_stdout"
# define STOP_SEM_NAME "/philo_stop"
# define STOP_MUTEX_NAME "/philo_stop_mutex"
# define PHILO_DEATH_SEM_ "/philo_death_"
# define PHILO_STOP_MUTEX_ "/philo_stop_mutex_"
# define PHILO_MEAL_MUTEX_ "/philo_meal_mutex_"
# define EXIT_DEATH 2
# define EXIT_ERROR EXIT_FAILURE

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdio.h>
# include <semaphore.h>
# include <pthread.h>

typedef struct s_philo t_philo;

typedef struct s_table
{
	long long	start_timestamp;
	int			n_philo;
	int			t_eat;
	int			t_sleep;
	int			t_die;
	int			times_eat;
	sem_t		*forks_sem;
	sem_t		*stdout_sem;
	pid_t		*children_pid; // maybe should be local to main
	t_philo		*philos;
	sem_t		*stop_sem;
	sem_t		*stop_mutex;
	int			shared_stop_flag;
}	t_table;

typedef struct s_philo
{
	char		meal_name[50];
	sem_t		*meal_mutex;
	long long	last_meal;
	// int			meal_count;
	int			id;
	char		death_name[50];
	sem_t		*death_mutex;
	int			exit_status;
	// char		stop_name[50];
	// sem_t		*stop_mutex;
	int			local_stop_flag;
	t_table		*table;
	pthread_t	life_thread;
	pthread_t	death_thread;
}	t_philo;

// Program startup
void			parse_args(t_table *table, int ac, char **av);
void			print_error_and_exit(char *err)
				__attribute__((noreturn));
long long		get_time_ms(void);

// General utils
int				ft_isspace(int c);
int				ft_isdigit(int c);
char			*ft_strdup(const char *s);
unsigned int	atou_safe(char *num, int *check);
char			*utoa(unsigned int num);
char			*lltoa(long long num);
void			smart_sleep(t_philo *philo, long long ms);

// Philo utils
void			print_message(t_philo *philo, char *msg);
void			pick_forks(t_philo *philo);
void			put_forks(t_philo *philo);
void			philo_eat(t_philo *philo, int *meal_count);
void			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);
void			philo_loop(t_philo *philo);

// Atomic utils
void			die(t_philo *philo);
int				philo_should_stop(t_philo *philo);
void			set_local_stop(t_philo *philo);

// Monitor utils
int				philo_died(t_philo *philo);

// Simulation init
void			init_philo(t_table *table, t_philo *philo, int id);
void			init(t_table *table);
void			set_sem_name(char *prefix, char *sem_name, t_philo *philo);

// Simulation routines
void			start(t_table *table);
void			start_philo(t_table *table, t_philo *philo, int id)
				__attribute__((noreturn));
void			*philo_death(void *arg);
void			*philo_life(void *arg);

// Termination and cleanup
void			wait_for_end(t_table *table);
void			cleanup(t_table *table);
void			cleanup_philo(t_philo *philo);

#endif