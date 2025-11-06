/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:07:21 by sabruma           #+#    #+#             */
/*   Updated: 2025/11/07 00:14:19 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stddef.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct s_philo	t_philo;

typedef struct s_table
{
	unsigned int	n_philo;
	unsigned int	t_die;
	unsigned int	t_eat;
	unsigned int	t_sleep;
	int				times_eat;	// Optional (-1 = not set)
	pthread_mutex_t	*forks;
	pthread_mutex_t	write_lock;
	pthread_mutex_t	death_lock;
	t_philo			*philos;
	long long		start_time;
	int				shared_stop;
	pthread_mutex_t	shared_stop_lock;
	pthread_t		monitor;
}	t_table;

typedef struct s_philo
{
	int				id;
	int				times_eat;
	long long		last_meal;	// Read by monitor
	pthread_t		thread;
	pthread_mutex_t	meal_lock;
	t_table			*table;
	int				left;
	int				right;
	int				stop_flag;
	pthread_mutex_t	stop_lock;
}	t_philo;

// General utils
int				ft_isspace(int c);
int				ft_isdigit(int c);
void			smart_sleep(t_table *table, long long ms);
long long		get_time_ms(void);
void			print_message(t_philo *philo, char *msg);
void			write_message(t_philo *philo, char *msg);
int				should_stop(t_philo *philo);
int				global_should_stop(t_table *table);
void			set_global_stop(t_table *table);
int				should_simulation_end(t_table *table,
					unsigned int *i, unsigned int *count_full);

// Philos API
void			pick_forks(t_philo *philo);
void			put_forks(t_philo *philo);
void			philo_eat(t_philo *philo);
void			philo_sleep(t_philo *philo);
void			philo_think(t_philo *philo);
int				philo_is_full(t_philo *philo);
int				philo_died(t_philo *philo);

// Initialization and thread routines
void			init(t_table *table);
void			init_philo(t_table *table, t_philo *philo, int id);
void			start(t_table *table);
void			*start_monitor(void *arg)
				__attribute__((hot));
void			*start_philo(void *arg)
				__attribute__((hot));

// Parsing
void			parse_args(t_table *table, int ac, char **av)
				__attribute__((nonnull(1)));
unsigned int	atou_safe(char *num, int *check)
				__attribute__((nonnull(1, 2)))
				__attribute__((warn_unused_result));

// Failure handling and resource cleanup
void			print_error_and_exit(char *msg)
				__attribute__((noreturn));
void			cleanup(t_table *table)
				__attribute__((nonnull(1)));