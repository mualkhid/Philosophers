/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initiate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:45:14 by mualkhid          #+#    #+#             */
/*   Updated: 2024/07/06 17:18:04 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_death(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	while (1)
	{
		sem_wait(table->check);
		if (get_current_time() - philo->last_meal > (size_t)table->time_to_starve)
		{
			display_message(philo, MESSAGE_DEATH);
			table->dead = 1;
			exit(1);
		}
		sem_post(table->check);
		if (table->dead)
			break ;
		usleep(1000);
		if (table->number_of_meals != -1
			&& philo->times_eaten >= table->number_of_meals)
			break ;
	}
	return (NULL);
}

void	exit_simulation(t_table *table)
{
	int	i;
	int	status;

	i = -1;
	while (++i < table->num_philos)
	{
		waitpid(-1, &status, 0);
		if (WEXITSTATUS(status) == 1)
		{
			i = -1;
			while (++i < table->num_philos)
				kill(table->philos[i].pid, SIGTERM);
			break ;
		}
	}
	sem_close(table->display);
	sem_close(table->check);
	sem_close(table->fork);
	sem_unlink("/sem_display");
	sem_unlink("/sem_check");
	sem_unlink("/sem_fork");
	free(table->philos);
}

size_t	get_current_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	wait_time(t_table *table, size_t time)
{
	size_t	t;

	t = get_current_time();
	while (!(table->dead))
	{
		if (get_current_time() - t >= time)
			break ;
		usleep(100);
	}
}
