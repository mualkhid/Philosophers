/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rel-fila <rel-fila@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/12 02:17:28 by rel-fila          #+#    #+#             */
/*   Updated: 2023/06/12 02:17:28 by rel-fila         ###   ########.fr       */
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
