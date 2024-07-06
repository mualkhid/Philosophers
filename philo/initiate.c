/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:44:06 by mualkhid          #+#    #+#             */
/*   Updated: 2024/07/06 17:18:04 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_death(t_table *tab)
{
	int	i;

	while (!tab->satiated)
	{
		i = -1;
		while (!tab->dead && ++i < tab->num_philos)
		{
			pthread_mutex_lock(&tab->check);
			if (get_current_time()
				- tab->philos[i].last_meal > (size_t)tab->time_to_starve)
			{
				display_message(&tab->philos[i], MESSAGE_DEATH);
				tab->dead = 1;
			}
			pthread_mutex_unlock(&tab->check);
			usleep(100);
		}
		if (tab->dead)
			break ;
		i = 0;
		while (tab->number_of_meals != -1 && i++ < tab->num_philos
			&& tab->philos[i].times_eaten >= tab->number_of_meals)
			i++;
		if (i == tab->num_philos)
			tab->satiated = 1;
	}
}

void	exit_simulation(t_table *tab, pthread_t *threads)
{
	int	i;

	i = -1;
	while (++i < tab->num_philos)
		pthread_join(threads[i], NULL);
	i = -1;
	while (++i < tab->num_philos)
		pthread_mutex_destroy(&tab->philos[i].fork);
	pthread_mutex_destroy(&tab->display);
	pthread_mutex_destroy(&tab->check);
	free(tab->philos);
	free(threads);
}

size_t	get_current_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	wait_time(t_table *tab, size_t time)
{
	size_t	t;

	t = get_current_time();
	while (!(tab->dead))
	{
		if (get_current_time() - t >= time)
			break ;
		usleep(100);
	}
}
