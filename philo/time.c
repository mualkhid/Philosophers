/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:44:56 by mualkhid          #+#    #+#             */
/*   Updated: 2024/07/05 15:44:57 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
static char	*get_message(int message)
{
	if (message == MESSAGE_FORK)
		return ("has taken a fork");
	if (message == MESSAGE_EAT)
		return ("is eating");
	if (message == MESSAGE_SLEEP)
		return ("is sleeping");
	if (message == MESSAGE_THINK)
		return ("is thinking");
	if (message == MESSAGE_DEATH)
		return ("died");
	return ("Error: not valid msg id");
}

void	display_message(t_philo *philo, int message)
{
	size_t	t;

	t = current_time() - philo->table->t_0;
	pthread_mutex_lock(&philo->table->display);
	if (!philo->table->dead && !philo->table->satiated)
	{
		printf("%ld ", t);
		printf(" %d ", philo->id);
		printf("%s", get_message(message));
		printf("\n");
	}
	pthread_mutex_unlock(&philo->table->display);
}

static void	philo_eat(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(&philo->fork);
	display_message(philo, MESSAGE_FORK);
	if (philo->table->number_of_philos == 1)
	{
		pass_time(table, table->time_to_starve);
		display_message(philo, MESSAGE_DEATH);
		pthread_mutex_unlock(&philo->fork);
		table->dead = 1;
		return ;
	}
	pthread_mutex_lock(&philo->next->fork);
	display_message(philo, MESSAGE_FORK);
	pthread_mutex_lock(&table->check);
	philo->times_eaten++;
	display_message(philo, MESSAGE_EAT);
	philo->last_meal = current_time();
	pthread_mutex_unlock(&table->check);
	pass_time(table, table->time_to_eat);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&philo->next->fork);
}

void	*life(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!table->dead && !table->satiated)
	{
		philo_eat(philo);
		display_message(philo, MESSAGE_SLEEP);
		pass_time(table, table->time_to_sleep);
		display_message(philo, MESSAGE_THINK);
	}
	return (NULL);
}
