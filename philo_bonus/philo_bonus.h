/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:45:27 by mualkhid          #+#    #+#             */
/*   Updated: 2024/07/05 15:45:28 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/wait.h>


enum e_msg {
	MESSAGE_FORK = 0,
	MESSAGE_EATING,
	MESSAGE_SLEEPING,
	MESSAGE_THINKING,
	MESSAGE_DEAD
};

typedef struct s_philo
{
	int				id;
	int				eaten_count;
	size_t			last_meal;
	struct s_philo	*next;
	struct s_philo	*prev;
	struct s_table	*table;
	pid_t			pid;
	pthread_t		death_checker;
}	t_philo;


typedef struct s_table
{
	int				time_to_starve;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				number_of_philosophers;
	int				satiated;
	int				dead;
	size_t			start_time;
	t_philo			*philosophers;
	sem_t			*display;
	sem_t			*check;
	sem_t			*fork;
}	t_table;

int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		verify_arguments(int argc, char *argv[], t_table *tab);
void	display_message(t_philo *philo, int message);
void	*life_cycle(void *arg);
void	exit_simulation(t_table *tab);
size_t	get_current_time(void);
void	wait_time(t_table *tab, size_t time);
void	*death_check(void *arg);

#endif
