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

void	initialize(t_table *tab)
{
	int	i;

	tab->dead = 0;
	tab->full = 0;
	tab->philos = (t_philo *)malloc(tab->num_philos * sizeof(t_philo));
	i = -1;
	while (++i < tab->num_philos)
	{
		tab->philos[i].id = i + 1;
		tab->philos[i].table = tab;
		tab->philos[i].times_eaten = 0;
		if (i + 1 == tab->num_philos)
			tab->philos[i].next = &tab->philos[0];
		else
			tab->philos[i].next = &tab->philos[i + 1];
		if (i == 0)
			tab->philos[i].prev = &tab->philos[tab->num_philos - 1];
		else
			tab->philos[i].prev = &tab->philos[i - 1];
		pthread_mutex_init(&tab->philos[i].fork, NULL);
	}
	pthread_mutex_init(&tab->display, NULL);
	pthread_mutex_init(&tab->check, NULL);
}

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

// void display_message(t_philo *philo, int message)
// {
//     size_t t;

//     pthread_mutex_lock(&philo->table->check); // Lock before accessing shared data
//     if (!philo->table->dead && !philo->table->full)
//     {
//         t = get_current_time() - philo->table->start_time;
//         pthread_mutex_lock(&philo->table->display);
//         printf("%ld ", t);
//         printf(" %d ", philo->id);
//         printf("%s", get_message(message));
//         printf("\n");
//         pthread_mutex_unlock(&philo->table->display);
//     }
//     pthread_mutex_unlock(&philo->table->check); // Unlock after accessing shared data
// }

void	display_message(t_philo *philo, int message)
{
	size_t	t;

	t = get_current_time() - philo->table->start_time;
	pthread_mutex_lock(&philo->table->display);
	if (!philo->table->dead && !philo->table->full)
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
	if (philo->table->num_philos == 1)
	{
		wait_time(table, table->time_to_starve);
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
	philo->last_meal = get_current_time();
	pthread_mutex_unlock(&table->check);
	wait_time(table, table->time_to_eat);
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
    while (1)
    {
        pthread_mutex_lock(&table->check); // Lock before checking shared data
        if (table->dead || table->full)
        {
            pthread_mutex_unlock(&table->check); // Unlock after checking
            break;
        }
        pthread_mutex_unlock(&table->check); // Unlock after checking

        philo_eat(philo); // Assuming philo_eat handles its own synchronization

        pthread_mutex_lock(&table->check); // Lock before accessing shared data
        if (!table->dead && !table->full)
            display_message(philo, MESSAGE_SLEEP);
        pthread_mutex_unlock(&table->check); // Unlock after accessing

        wait_time(table, table->time_to_sleep); // Assuming wait_time handles its own synchronization

        pthread_mutex_lock(&table->check); // Lock before accessing shared data
        if (!table->dead && !table->full)
            display_message(philo, MESSAGE_THINK);
        pthread_mutex_unlock(&table->check); // Unlock after accessing
    }
    return (NULL);
}

// void	*life(void *arg)
// {
// 	t_philo	*philo;
// 	t_table	*table;

// 	philo = (t_philo *)arg;
// 	table = philo->table;
// 	if (philo->id % 2 == 0)
// 		usleep(1000);
// 	while (!table->dead && !table->full)
// 	{
// 		philo_eat(philo);
// 		display_message(philo, MESSAGE_SLEEP);
// 		wait_time(table, table->time_to_sleep);
// 		display_message(philo, MESSAGE_THINK);
// 	}
// 	return (NULL);
// }


// void *life(void *arg) {
//     t_philo *philo = (t_philo *)arg;
//     t_table *table = philo->table;

//     if (philo->id % 2 == 0)
//         usleep(1000);

//     while (1) {
//         // Lock the mutex before accessing shared data
//         pthread_mutex_lock(&table->check);
//         if (table->dead || table->full) {
//             pthread_mutex_unlock(&table->check);
//             break;
//         }
//         pthread_mutex_unlock(&table->check);

//         philo_eat(philo);

//         // Lock the mutex before displaying messages or accessing shared data
//         pthread_mutex_lock(&table->check);
//         if (!table->dead && !table->full)
//             display_message(philo, MESSAGE_SLEEP);
//         pthread_mutex_unlock(&table->check);

//         wait_time(table, table->time_to_sleep);

//         // Lock the mutex before displaying messages or accessing shared data
//         pthread_mutex_lock(&table->check);
//         if (!table->dead && !table->full)
//             display_message(philo, MESSAGE_THINK);
//         pthread_mutex_unlock(&table->check);
//     }

//     return (NULL);
// }
