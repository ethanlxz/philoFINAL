/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: etlaw <ethanlxz@gmail.com>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 22:27:27 by etlaw             #+#    #+#             */
/*   Updated: 2023/07/23 22:55:43 by etlaw            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>

/*
2 types of state in this program

thinking = program is currently running
end = one of the philos is dead or all the philos has met the min_eat quota;
*/
# define THINKING 1
# define END 2

// Strings for philo activity
# define STR_FORK "has taken a fork"
# define STR_EAT "is eating"
# define STR_SLEEP "is sleeping"
# define STR_THINK "is thinking"
# define STR_DIED "died"

typedef struct timeval	t_timeval;

// info for all the program parameters
typedef struct s_info
{
	int						philos;
	int						die_time;
	int						eat_time;
	int						sleep_time;
	int						min_eat;
	int						met_quota;
	int						start_time;
	pid_t					*philo_pid;
	sem_t					*s_print;
	sem_t					*forks;
	sem_t					*s_eat;
	sem_t					*s_end;
	sem_t					*s_quota;
}	t_info;

// philo struct
typedef struct s_philo
{
	int						id;
	t_info					*info;
	int						last_ate;
	t_timeval				time_lastate;
	int						total_ate;
	sem_t					*s_print;
	sem_t					*forks;
	sem_t					*s_eat;
	sem_t					*s_end;
	sem_t					*s_quota;
}	t_philo;

// init.c
int		init_val(int ac, char **av, t_info *info);
int		init_sem(t_info *info);

// philo.c
int		philo(t_info *info);

// philo_actions.c
void	philo_eat(t_philo *p);
void	philo_sleep(t_philo *p);
void	philo_speak(t_philo *p, char *msg);

// utils.c
int		ft_atoi(const char *str);
int		get_time(void);
void	ft_usleep(int time, int num);
void	kill_philo_pid(t_info *info);
int		pl_time(void);

// check_philo
void	*check_philo(void *ptr);

// time
int		pl_time(void);
void	pl_meal_time(t_philo *philo);
void	pl_usleep(int time);
int		time_get(t_timeval *time);
void	time_set(t_timeval *time);

#endif