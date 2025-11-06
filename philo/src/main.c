/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabruma <sabruma@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 00:07:09 by sabruma           #+#    #+#             */
/*   Updated: 2025/11/07 00:12:38 by sabruma          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	t_table	table;

	if (ac != 5 && ac != 6)
		print_error_and_exit("Argument count must be 5 or 6");
	parse_args(&table, ac, av);
	init(&table);
	start(&table);
	while (!global_should_stop(&table))
		smart_sleep(&table, 1);
	cleanup(&table);
	return (0);
}
