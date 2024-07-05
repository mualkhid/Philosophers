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

#include "main.h"

time_t	get_time_in_ms(void)
{
	time_t			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

void	ft_sleep(int time)
{
	time_t	now;

	now = get_time_in_ms();
	while (get_time_in_ms() - now < time)
		usleep(100);
}
