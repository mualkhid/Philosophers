/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:45:54 by mualkhid          #+#    #+#             */
/*   Updated: 2024/07/06 17:27:26 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static char	*get_message(int message)
{
	if (message == MESSAGE_FORK)
		return (" has taken a fork");
	if (message == MESSAGE_EAT)
		return (" is eating");
	if (message == MESSAGE_SLEEP)
		return (" is sleeping");
	if (message == MESSAGE_THINK)
		return (" is thinking");
	if (message == MESSAGE_DEATH)
		return (" died");
	return ("Error: not valid msg id");
}

void	display_message(t_philo *philo, int message)
{
	size_t	t;

	t = get_current_time() - philo->table->start_time;
	sem_wait(philo->table->display);
	if (!philo->table->dead && !philo->table->satiated)
	{
		printf("%6ld", t);
		printf(" %3d ", philo->id);
		printf("%s", get_message(message));
		printf("\n");
	}
	sem_post(philo->table->display);
}

static void	philosopher_eats(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	sem_wait(philo->table->fork);
	display_message(philo, MESSAGE_FORK);
	if (table->num_philos == 1)
	{
		wait_time(table, table->time_to_starve);
		display_message(philo, MESSAGE_DEATH);
		table->dead = 1;
		return ;
	}
	sem_wait(philo->table->fork);
	display_message(philo, MESSAGE_FORK);
	sem_wait(philo->table->check);
	philo->times_eaten++;
	display_message(philo, MESSAGE_EAT);
	philo->last_meal = get_current_time();
	sem_post(philo->table->check);
	wait_time(table, table->time_to_eat);
	sem_post(philo->table->fork);
	sem_post(philo->table->fork);
}

void	*life(void *arg)
{
	t_philo	*philo;
	t_table	*table;

	philo = (t_philo *)arg;
	table = philo->table;
	philo->last_meal = table->start_time;
	pthread_create(&philo->death_checker, NULL, check_death, (void *)philo);
	if (philo->id % 2 == 0)
		usleep(1000);
	while (!table->dead)
	{
		philosopher_eats(philo);
		if (table->number_of_meals != -1 && philo->times_eaten >= table->number_of_meals)
			break ;
		display_message(philo, MESSAGE_SLEEP);
		wait_time(table, table->time_to_sleep);
		display_message(philo, MESSAGE_THINK);
	}
	pthread_join(philo->death_checker, NULL);
	exit(0);
}
