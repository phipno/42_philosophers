/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:57:37 by pnolte            #+#    #+#             */
/*   Updated: 2022/10/17 15:11:05 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*init_each_philo(t_mainS *s)
{
	int j;
	t_philo *phi;
	
	phi = malloc(sizeof(t_philo) * s->nbr_phi);
	if (phi == NULL)
		s->error = 102;
	j = 0;
	while (j < s->nbr_phi)
	{
		phi[j].id_phi = j + 1;
		phi[j].timer_die = s->time_die;
		phi[j].timer_eat = s->time_eat;
		phi[j].timer_sleep = s->time_sleep;
		if (s->c_argc == 6)
			phi[j].count_phi_eat = s->nbr_times_phi_eat;
		else
			phi[j].count_phi_eat = 0;
		phi[j].start_mili = s->start_mili;
		phi[j].error = 0;
		phi[j].mainstr = s; 
		j++;
	}
	return(phi);
}

/*
UNIX epoch, on midnight UTC on January 1, 1970, might be risky to
set here.
*/

int init_struct(t_mainS *s, char **argv)
{
	int	j;
	
	j = 1;
	s->nbr_phi = ft_atoi(argv[j++]);
	s->time_die = ft_atoi(argv[j++]);
	s->time_eat = ft_atoi(argv[j++]);
	s->time_sleep = ft_atoi(argv[j++]);
	if (s->c_argc == 6)
		s->nbr_times_phi_eat = ft_atoi(argv[j]);
	else
		s->nbr_times_phi_eat = 0;
	s->nbr_fork = s->nbr_phi;
	if (gettimeofday(&s->time, NULL) != 0)
		s->error = 102;
	s->fork = malloc(sizeof(pthread_mutex_t) * s->nbr_fork);
	if (s->fork == NULL)
		s->error = 102;
	s->start_mili = (s->time.tv_sec * 1000) + (s->time.tv_usec / 1000);
	s->phi = init_each_philo(s);
	return(s->error);
}

