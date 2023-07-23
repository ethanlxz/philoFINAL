/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlaw <ethanlxz@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 18:21:22 by etlaw             #+#    #+#             */
/*   Updated: 2023/07/23 22:59:36 by etlaw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

void	philo_eat(t_philo *p)
{
	sem_wait(p->forks);
	philo_speak(p, STR_FORK);
	sem_wait(p->forks);
	philo_speak(p, STR_FORK);
	++p->total_ate;
	if (p->info->met_quota <= p->info->philos)
		philo_speak(p, STR_EAT);
	if (p->total_ate == p->info->min_eat)
	{
		sem_wait(p->s_quota);
		++p->info->met_quota;
		sem_post(p->s_quota);
	}
	sem_wait(p->s_eat);
	pl_meal_time(p);
	sem_post(p->s_eat);
	ft_usleep(p->info->eat_time, p->info->philos);
	sem_post(p->forks);
	sem_post(p->forks);
}

void	philo_sleep(t_philo *p)
{
	philo_speak(p, STR_SLEEP);
	ft_usleep(p->info->sleep_time, p->info->philos);
}

void	philo_speak(t_philo *p, char *msg)
{
	sem_wait(p->s_print);
	printf("%04i %i %s\n", pl_time() - p->info->start_time, p->id, msg);
	sem_post(p->s_print);
}
