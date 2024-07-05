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

#include "main.h"

int	main(int ac, char **av)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (ac - 1 == 4 || ac - 1 == 5)
	{
		if (check_valid_input(ac, av))
			return (1);
		initiate_var(ac, av, var);
		start_simulation(var);
	}
	else
		printf("Usage: ./philo <# philosophers> <time to die> <time to eat>\
				<time to sleep> [# times each philosopher must eat]\n");
	return (0);
}
