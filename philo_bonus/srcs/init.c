/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 18:26:20 by etlaw             #+#    #+#             */
/*   Updated: 2023/07/24 03:50:25 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static int	check_val(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9' || i > 10)
			return (0);
		i++;
	}
	if (i == 0)
		return (0);
	return (1);
}

int	init_val(int ac, char **av, t_info *info)
{
	if (!check_val(av[1]) || !check_val(av[2]) || !check_val(av[3])
		|| !check_val(av[4]) || (ac == 6 && !check_val(av[5])))
		return (0);
	info->philos = ft_atoi(av[1]);
	info->die_time = ft_atoi(av[2]);
	info->eat_time = ft_atoi(av[3]);
	info->sleep_time = ft_atoi(av[4]);
	if (ac == 6)
		info->min_eat = ft_atoi(av[5]);
	else
		info->min_eat = -1;
	info->met_quota = 0;
	info->start_time = pl_time();
	if (info->philos <= 0 || info->die_time <= 0
		|| info->eat_time <= 0 || info->sleep_time <= 0
		|| (ac == 6 && info->min_eat <= -1))
		return (0);
	return (1);
}

int	init_sem(t_info *info)
{
	sem_unlink("FORKS");
	info->forks = sem_open("FORKS", O_CREAT | O_EXCL, 0644, info->philos);
	if (info->forks == SEM_FAILED)
		return (1);
	sem_unlink("S_EAT");
	info->s_eat = sem_open("S_EAT", O_CREAT, 0644, 1);
	if (info->s_eat == SEM_FAILED)
		return (1);
	sem_unlink("S_PRINT");
	info->s_print = sem_open("S_PRINT", O_CREAT, 0644, 1);
	if (info->s_print == SEM_FAILED)
		return (1);
	sem_unlink("S_QUOTA");
	info->s_quota = sem_open("S_QUOTA", O_CREAT, 0644, 1);
	if (info->s_quota == SEM_FAILED)
		return (1);
	sem_unlink("S_END");
	info->s_end = sem_open("S_END", O_CREAT, 0644, 0);
	if (info->s_end == SEM_FAILED)
		return (1);
	return (0);
}
