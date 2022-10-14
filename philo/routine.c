/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:33:07 by pnolte            #+#    #+#             */
/*   Updated: 2022/10/14 16:28:06 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long current_time(t_mainS *s)
{
	struct timeval curr;
	long long ms;
	
	if (gettimeofday(&curr, NULL) != 0)
		s->error = 102;
	ms = ((curr.tv_sec * 1000) + (curr.tv_usec / 1000)) - s->start_mili;
	return (ms);
}

bool	death_checker(t_mainS *s)
{
	int i;
	
	i  = 0;
	while (i < s->nbr_phi)
	{
		if (s->phi[i].count_phi_eat > s->nbr_times_phi_eat)
			return(true);
		i++;
	}
	return(false);
}

void	*routine(void *arg)
{
	t_mainS *s;
	
	s = (t_mainS*)arg;
	while ()
	{
	}
	return (NULL);
}

int start_simulation(t_mainS *s)
{
	int i;
	pthread_t tid[s->nbr_phi];
	
	i = 0;
	// printf("NBR_phi %d\n", s->nbr_phi);
	while (i < s->nbr_fork)
	{
		pthread_mutex_init(&s->fork[i], NULL);
		i++;
	}	
	i = 0;
	while (i < s->nbr_phi)
	{
		s->id = i + 1;
		if (pthread_create(&tid[i] , NULL, &routine, &s) != 0)
			return (102);
		i++;
	}
	i = 0;
	while (i < s->nbr_phi)
	{
		if (pthread_join(tid[i], NULL) != 0)
			return (102);
		i++;
	}
	i = 0;
	while (i < s->nbr_fork)
	{
		pthread_mutex_destroy(&s->fork[i]);
		i++;
	}	
	return(0);
}