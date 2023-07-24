/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlaw <ethanlxz@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 20:49:23 by etlaw             #+#    #+#             */
/*   Updated: 2023/07/24 22:19:09 by etlaw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static	void	*philo_brain(t_philo *p)
{
	pthread_t	check;

	pl_meal_time(p);
	pthread_create(&check, NULL, check_philo, (void *)p);
	pthread_detach(check);
	while (1)
	{
		philo_eat(p);
		sem_wait(p->s_quota);
		if (p->info->min_eat != -1 && p->info->met_quota >= 1)
		{
			sem_post(p->s_quota);
			break ;
		}
		sem_post(p->s_quota);
		philo_sleep(p);
		philo_speak(p, STR_THINK);
	}
	sem_post(p->s_end);
	exit(0);
}

int	run_philo(t_info *info, t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < info->philos)
	{
		info->philo_pid[i] = fork();
		if (info->philo_pid[i] == -1)
			printf("Fork Error in Philo !\n");
		else if (info->philo_pid[i] == 0)
		{
			philo_brain(&philo[i]);
		}
	}
	return (0);
}

static t_philo	init_philo(int id, t_info	*info)
{
	t_philo	philo;

	philo.id = id + 1;
	philo.info = info;
	philo.s_print = info->s_print;
	philo.total_ate = 0;
	philo.s_eat = info->s_eat;
	philo.s_end = info->s_end;
	philo.s_quota = info->s_quota;
	philo.forks = info->forks;
	return (philo);
}

static t_philo	*create_philo(t_info *info)
{
	int				id;
	t_philo			*philo;

	id = -1;
	philo = malloc(sizeof(t_philo) * info->philos);
	info->philo_pid = malloc(sizeof(pid_t) * info->philos);
	while (++id < info->philos)
	{
		philo[id] = init_philo(id, info);
		if (philo == NULL)
			return (NULL);
	}
	return (philo);
}

int	philo(t_info *info)
{
	t_philo			*philo;

	if (init_sem(info) == 1)
		return (1);
	philo = create_philo(info);
	if (!philo)
		return (1);
	run_philo(info, philo);
	kill_philo_pid(info);
	sem_close(info->forks);
	sem_close(info->s_eat);
	sem_close(info->s_end);
	sem_close(info->s_print);
	sem_close(info->s_quota);
	free(philo);
	free(info->philo_pid);
	return (0);
}
