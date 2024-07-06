/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:44:19 by mualkhid          #+#    #+#             */
/*   Updated: 2024/07/05 15:44:20 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>


enum e_msg {
	MESSAGE_FORK = 0,
	MESSAGE_EAT,
	MESSAGE_SLEEP,
	MESSAGE_THINK,
	MESSAGE_DEATH
};

typedef struct s_philo
{
	int				id;
	int				times_eaten;
	size_t			last_meal;
	pthread_mutex_t	fork;
	struct s_philo	*next;
	struct s_philo	*prev;
	struct s_table	*table;
}	t_philo;

typedef struct s_table
{
	int				time_to_starve;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_meals;
	int				number_of_philos;
	int				satiated;
	int				dead;
	size_t			t_0;
	t_philo			*philos;
	pthread_mutex_t	display;
	pthread_mutex_t	check;
}	t_table;

int		ft_isdigit(int c);
size_t	ft_strlen(const char *s);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		ft_atoi(const char *str);
int		verify_args(int argc, char *argv[], t_table *tab);
void	display_message(t_philo *philo, int message);
void	*life(void *arg);
void	check_death(t_table *tab);
void	exit_simulation(t_table *tab, pthread_t *threads);
size_t	current_time(void);
void	pass_time(t_table *tab, size_t time);

#endif
