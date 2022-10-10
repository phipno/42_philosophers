/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:33:07 by pnolte            #+#    #+#             */
/*   Updated: 2022/10/10 15:35:28 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	forks_and_food(t_mainS *s)
{
	if (s->id % 2 != 0)
	{
		pthread_mutex_lock(&s->fork[s->id]);
		printf("p[%d] has taken a fork: %d\n", s->id, s->id);
		pthread_mutex_lock(&s->fork[s->id + 1]);
		printf("p[%d] has taken a fork: %d\n", s->id, s->id + 1);
		printf("p[%d] is eating\n", s->id);
		usleep(s->time_eat);
		pthread_mutex_unlock(&s->fork[s->id]);
		pthread_mutex_unlock(&s->fork[s->id + 1]);
	}
}

bool	death_checker(t_mainS *s)
{
	int i;
	
	i  = 0;
	while (i < s->nbr_phi)
	{
		if (s->phi[i].timer_die == 0)
			return(true);
		i++;
	}
	return(false);
}

void	*routine(void *arg)
{
	t_mainS *s;
	
	s = (t_mainS*)arg;
	while (death_checker(s) != true)
	{
		forks_and_food(s);
	}
	return (NULL);
}

int start_simulation(t_mainS *s)
{
	int i;
	pthread_t tid[s->nbr_phi];
	
	i = 0;
	// printf("NBR_phi %d\n", s->nbr_phi);
	pthread_mutex_init(s->fork, NULL);
	while (i < s->nbr_phi)
	{
		s->id = i + 1;
		if (pthread_create(&tid[i], NULL, &routine, (void*)s) != 0)
			return (102);
		usleep(150);
		i++;
	}
	i = 0;
	while (i < s->nbr_phi)
	{
		if (pthread_join(tid[i], NULL) != 0)
			return (102);
		i++;
	}
	pthread_mutex_destroy(s->fork);
	return(0);
}