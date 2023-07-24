/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yichan <yichan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 22:52:39 by etlaw             #+#    #+#             */
/*   Updated: 2023/07/24 22:13:26 by yichan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo_bonus.h"

static void	start(int ac, char **av, t_info *info)
{
	if (!init_val(ac, av, info))
	{
		printf("Invalid parameters!\n");
		return ;
	}
	if (philo(info))
	{
		printf("Error! Program not created properly.\n");
		return ;
	}
}

int	main(int ac, char **av)
{
	t_info	info;

	if (ac == 5 || ac == 6)
	{
		start(ac, av, &info);
	}
	else
		printf("Too much or too less arguments! Try again.\n");
	return (0);
}
