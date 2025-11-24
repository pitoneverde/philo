#include "bonus_philo.h"
#include <sys/wait.h>
#include <signal.h>

void kill_all_children(t_table *table);

void	wait_for_end(t_table *table)
{
	int		status;
	int		exited;
	int		exit_code;
	pid_t	pid;

	exited = 0;
	while (exited < table->n_philo)
	{
		pid = waitpid(0, &status, 0);
		if (pid == -1)
			break;
		exited++;
		if (WIFEXITED(status))
		{
			exit_code = WEXITSTATUS((status));
			if (exit_code == EXIT_DEATH || exit_code == EXIT_ERROR)
				kill_all_children(&table);
		}
	}
}

void kill_all_children(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->n_philo)
	{
		if (table->children_pid[i] > 0)
			kill(table->children_pid[i], SIGTERM);
		i++;
	}
}