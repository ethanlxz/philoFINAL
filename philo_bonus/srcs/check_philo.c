/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlaw <ethanlxz@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 22:57:20 by etlaw             #+#    #+#             */
/*   Updated: 2023/07/23 23:06:10 by etlaw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

int	lmeal_interv(t_philo *philo)
{
	int	interval;

	interval = pl_time() - time_get(&philo->time_lastate);
	return (interval);
}

static int	philo_dead(t_philo *p)
{
	sem_wait(p->s_quota);
	sem_wait(p->s_eat);
	if (p->info-> min_eat != 0 && lmeal_interv(p) >= p->info->die_time)
	{
		sem_post(p->s_eat);
		sem_wait(p->s_print);
		printf("%04i %i %s\n", (pl_time() - p->info->start_time),
			p->id, STR_DIED);
		exit(1);
		return (1);
	}
	sem_post(p->s_eat);
	sem_post(p->s_quota);
	return (0);
}

void	*check_philo(void *ptr)
{
	t_philo	*p;

	p = (t_philo *)ptr;
	while (1)
	{
		philo_dead(p);
		usleep(50 * p->info->philos);
	}
}
