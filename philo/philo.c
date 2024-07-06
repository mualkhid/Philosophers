/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:44:12 by mualkhid          #+#    #+#             */
/*   Updated: 2024/07/06 17:18:04 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	error(void)
{
	write(2, "Error! invalid arguments\n", 26);
	return (1);
}

int	main(int argc, char *argv[])
{
	int			i;
	t_table		tab;
	pthread_t	*threads;

	if ((argc < 5 || argc > 6) || verify_args(argc, argv, &tab))
		return (error());
	threads = (pthread_t *)malloc(tab.num_philos * sizeof(pthread_t));
	tab.start_time = get_current_time();
	i = -1;
	while (++i < tab.num_philos)
	{
		if (pthread_create(&threads[i], NULL, &life, &tab.philos[i]))
		{
			write(2, "Error! cannot create thread\n", 28);
			free(tab.philos);
			free(threads);
			return (1);
		}
		pthread_mutex_lock(&tab.check);
		tab.philos[i].last_meal = tab.start_time;
		pthread_mutex_unlock(&tab.check);
	}
	check_death(&tab);
	exit_simulation(&tab, threads);
	return (0);
}
