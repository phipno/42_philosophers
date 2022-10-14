/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:42:06 by pnolte            #+#    #+#             */
/*   Updated: 2022/10/14 16:04:31 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
#include <sys/time.h>

typedef struct s_philo
{
	int error;
	int id_phi;
	int timer_die;
	int timer_eat;
	int timer_sleep;
	int count_phi_eat;
	long long curr_mili;
	struct s_mainS *doom;
}		t_philo;

typedef struct s_mainS
{
	t_philo *phi;
	int id;
	int error;
	int	c_argc;
	int nbr_phi;
	int nbr_fork;
	int	time_die;
	int	time_eat;
	int time_sleep;
	int	nbr_times_phi_eat;
	pthread_mutex_t *fork;
	struct timeval time;
	long long start_mili;
}		t_mainS;

int	ft_atoi(const char *str);

int		init_struct(t_mainS *s, char **argv);
t_philo	*init_each_philo(t_mainS *s);
long long transform_milli(t_mainS *s);


int start_simulation(t_mainS *s);
void	*routine(void *arg);

#endif