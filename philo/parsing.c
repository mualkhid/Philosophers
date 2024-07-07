/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mualkhid <mualkhid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 15:44:24 by mualkhid          #+#    #+#             */
/*   Updated: 2024/07/06 17:18:04 by mualkhid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	verify_numbers(int argc, char *argv[])
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

static int	verify_integer(char *s)
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

static int	validate_args(int argc, char *argv[])
{
	int	i;

	if (verify_numbers(argc, argv))
		return (1);
	i = 0;
	while (++i < argc)
	{
		if (verify_integer(argv[i]))
			return (1);
	}
	return (0);
}

int	verify_args(int argc, char *argv[], t_table *tab)
{
	if (validate_args(argc, argv))
		return (1);
	tab->num_philos = ft_atoi(argv[1]);
	tab->time_to_starve = ft_atoi(argv[2]);
	tab->time_to_eat = ft_atoi(argv[3]);
	tab->time_to_sleep = ft_atoi(argv[4]);
	tab->number_of_meals = -1;
	if (argc == 6)
		tab->number_of_meals = ft_atoi(argv[5]);
	initialize(tab);
	return (0);
}
