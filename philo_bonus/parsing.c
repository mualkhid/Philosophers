/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:45:39 by mualkhid          #+#    #+#             */
/*   Updated: 2024/07/06 17:18:04 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	check_numbers(int argc, char *argv[])
{
	int	i;
	int	j;

	i = 0;
	while (++i < argc)
	{
		j = -1;
		if (argv[i][0] == '-')
			return (1);
		else if (argv[i][0] == '+')
			j++;
		if (!ft_isdigit(argv[i][j + 1]))
			return (1);
		while (argv[i][++j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (1);
		}
	}
	return (0);
}

static int	check_integer(char *s)
{
	size_t	len;

	len = ft_strlen(s);
	if (*s == '+' && s++)
		len--;
	while (*s == '0' && *s && len--)
		s++;
	if (len > 10)
		return (1);
	else if (len < 10)
		return (0);
	if (ft_strncmp(s, "2147483648", 10) >= 0)
		return (1);
	return (0);
}

static void	initialize(t_table *tab)
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
	}
}

static void	initialize_semaphores(t_table *tab)
{
	tab->display = sem_open("/sem_display", O_CREAT, 0644, 1);
	tab->check = sem_open("/sem_check", O_CREAT, 0644, 1);
	tab->fork = sem_open("/sem_fork", O_CREAT, 0644, tab->num_philos);
	if (tab->display == SEM_FAILED || tab->check == SEM_FAILED
		|| tab->fork == SEM_FAILED)
	{
		write(2, "Error! sem_open failed\n", 23);
		exit(1);
	}
}

int	verify_args(int argc, char *argv[], t_table *tab)
{
	int	i;

	if (check_numbers(argc, argv))
		return (1);
	i = 0;
	while (++i < argc)
	{
		if (check_integer(argv[i]))
			return (1);
	}
	tab->num_philos = ft_atoi(argv[1]);
	tab->time_to_starve = ft_atoi(argv[2]);
	tab->time_to_eat = ft_atoi(argv[3]);
	tab->time_to_sleep = ft_atoi(argv[4]);
	tab->number_of_meals = -1;
	if (argc == 6)
		tab->number_of_meals = ft_atoi(argv[5]);
	initialize(tab);
	initialize_semaphores(tab);
	return (0);
}
