/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:45:18 by mualkhid          #+#    #+#             */
/*   Updated: 2024/07/05 15:45:19 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
static int	error(void)
{
	write(2, "Error! invalid arguments\n", 26);
	return (1);
}

int	main(int argc, char *argv[])
{
	int			i;
	t_table		table;

	// Check if the number of arguments is correct or if arguments are invalid
	if ((argc < 5 || argc > 6) || verify_arguments(argc, argv, &table))
		return (error());

	// Initialize the start time of the simulation
	table.start_time = get_current_time();

	// Create child processes (philosophers)
	i = -1;
	while (++i < table.number_of_philosophers)
	{
		table.philosophers[i].pid = fork();
		if (table.philosophers[i].pid == -1)
		{
			write(2, "Error! fork failed\n", 19);
			exit(1);
		}
		if (table.philosophers[i].pid == 0)
			life_cycle((void *)&table.philosophers[i]); // Start life cycle for philosopher in child process
	}

	// Wait for all philosophers to finish
	exit_simulation(&table);

	return (0);
}
