/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:45:54 by mualkhid          #+#    #+#             */
/*   Updated: 2024/07/05 15:45:55 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"
static char *get_message(int message)
{
    if (message == MESSAGE_FORK)
        return (" has taken a fork");
    if (message == MESSAGE_EAT)
        return (" is eating");
    if (message == MESSAGE_SLEEP)
        return (" is sleeping");
    if (message == MESSAGE_THINK)
        return (" is thinking");
    if (message == MESSAGE_DEAD)
        return (" died");
    return ("Error: not valid msg id");
}


void display_message(t_philo *philo, int message)
{
    size_t t;

    t = current_time() - philo->table->start_time;
    sem_wait(philo->table->display);
    if (!philo->table->dead && !philo->table->satiety)
    {
        printf("%6ld", t);
        printf(" %3d ", philo->id);
        printf("%s", get_message(message));
        printf("\n");
    }
    sem_post(philo->table->display);
}


static void philosopher_eats(t_philo *philo)
{
    t_table *table;

    table = philo->table;
    sem_wait(philo->table->forks);
    display_message(philo, MESSAGE_FORK);
    if (table->num_philosophers == 1)
    {
        pass_time(table, table->starvation_time);
        display_message(philo, MESSAGE_DEAD);
        table->dead = 1;
        return ;
    }
    sem_wait(philo->table->forks);
    display_message(philo, MESSAGE_FORK);
    sem_wait(philo->table->verify);
    philo->eat_count++;
    display_message(philo, MESSAGE_EAT);
    philo->last_meal = current_time();
    sem_post(philo->table->verify);
    pass_time(table, table->eating_time);
    sem_post(philo->table->forks);
    sem_post(philo->table->forks);
}


void *life(void *arg)
{
    t_philo *philo;
    t_table *table;

    philo = (t_philo *)arg;
    table = philo->table;
    philo->last_meal = table->start_time;
    pthread_create(&philo->check_dead, NULL, check_death, (void *)philo);
    if (philo->id % 2 == 0)
        usleep(1000);
    while (!table->dead)
    {
        philosopher_eats(philo);
        if (table->meal_count != -1 && philo->eat_count >= table->meal_count)
            break ;
        display_message(philo, MESSAGE_SLEEP);
        pass_time(table, table->sleep_time);
        display_message(philo, MESSAGE_THINK);
    }
    pthread_join(philo->check_dead, NULL);
    exit (0);
}
