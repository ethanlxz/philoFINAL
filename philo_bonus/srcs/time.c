/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlaw <ethanlxz@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 22:15:38 by etlaw             #+#    #+#             */
/*   Updated: 2023/07/23 22:59:57 by etlaw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

// kill me.

int	pl_time(void)
{
	t_timeval	time;

	gettimeofday(&time, 0);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

void	pl_usleep(int time)
{
	time_t	start;

	start = pl_time();
	while (pl_time() - start < time)
		usleep (250);
}

void	pl_meal_time(t_philo *philo)
{
	int	temp;

	temp = pl_time();
	philo->last_ate = temp;
	time_set(&philo->time_lastate);
}

int	time_get(t_timeval *time)
{
	int	status;

	status = (time->tv_sec) * 1000
		+ (time->tv_usec) / 1000;
	return (status);
}

void	time_set(t_timeval *time)
{
	gettimeofday(time, 0);
}
