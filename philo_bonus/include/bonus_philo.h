#ifndef BONUS_PHILO_H
# define BONUS_PHILO_H
# define FORKS_SEM_NAME "/philo_forks"
# define STDOUT_SEM_NAME "/philo_stdout"
# define PHILO_SEM_PREFIX "/philo_"
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
}	t_table;

typedef struct s_philo
{
	long long	last_meal;
	int			id;
	char		sem_name[50];
	sem_t		*death_sem;			//should be opened by main_start to make the process signal-safe
	t_table		*table;
	pthread_t	life_thread;
	pthread_t	death_thread;
}	t_philo;

void			parse_args(t_table *table, int ac, char **av);
void			print_error_and_exit(char *err)
				__attribute__((noreturn));
long long		get_time_ms(void);

int				ft_isspace(int c);
int				ft_isdigit(int c);
char			*ft_strdup(const char *s);
unsigned int	atou_safe(char *num, int *check);
char			*utoa(unsigned int num);
char			*lltoa(long long num);

void			init_philo(t_table *table, t_philo *philo, int id);
void			init(t_table *table);
void			set_sem_name(t_philo *philo);

void			start(t_table *table);
void			start_philo(t_table *table, t_philo *philo, int id)
				__attribute__((noreturn));
void			*philo_death(void *arg);
void			*philo_life(void *arg);

void			wait_for_end(t_table *table);
void			cleanup(t_table *table);
void			cleanup_philo(t_philo *philo);

#endif