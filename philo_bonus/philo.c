/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:45:18 by mualkhid          #+#    #+#             */
/*   Updated: 2024/07/06 17:25:17 by mualkhid         ###   ########.fr       */
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
	int		i;
	t_table	table;

	if ((argc < 5 || argc > 6) || verify_args(argc, argv, &table))
		return (error());
	table.start_time = get_current_time();
	i = -1;
	while (++i < table.num_philos)
	{
		table.philos[i].pid = fork();
		if (table.philos[i].pid == -1)
		{
			write(2, "Error! fork failed\n", 19);
			exit(1);
		}
		if (table.philos[i].pid == 0)
			life((void *)&table.philos[i]);
	}
	exit_simulation(&table);
	return (0);
}
