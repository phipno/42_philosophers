/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 14:33:07 by pnolte            #+#    #+#             */
/*   Updated: 2022/10/17 17:51:16 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long current_time(t_philo *phi)
{
	struct timeval curr;
	long long ms;
	
	if (gettimeofday(&curr, NULL) != 0)
		phi->error = 102;
	ms = ((curr.tv_sec * 1000) + (curr.tv_usec / 1000)) - phi->start_mili;
	return (ms);
}

void	sleepy_philo(t_philo *phi)
{
	phi->curr_mili = current_time(phi);
	if (phi->timer_die < phi->timer_sleep)
	{
		while (phi->curr_mili + phi->timer_die > current_time(phi))
		printf("%lld %d died\n", current_time(phi), phi->id_phi);
		pthread_mutex_lock(&phi->mainstr->lock);
		phi->mainstr->death = 1;
		pthread_mutex_unlock(&phi->mainstr->lock);
	}
	printf("%lld %d is sleeping\n", current_time(phi), phi->id_phi);
	while(phi->curr_mili + phi->timer_sleep > current_time(phi));
}

void	forks_and_food(t_philo *phi)
{
	phi->curr_mili = current_time(phi);
	pthread_mutex_lock(&phi->mainstr->fork[phi->id_phi - 1]);
	printf("%lld %d has taken a fork\n", current_time(phi), phi->id_phi);
	pthread_mutex_lock(&phi->mainstr->fork[phi->id_phi]);
	printf("%lld %d has taken a fork\n", current_time(phi), phi->id_phi);
	if (phi->timer_die < phi->timer_eat)
		{
			while (phi->curr_mili + phi->timer_die > current_time(phi))
			printf("%lld %d died\n", current_time(phi), phi->id_phi);
			pthread_mutex_lock(&phi->mainstr->lock);
			phi->mainstr->death = 1;
			pthread_mutex_unlock(&phi->mainstr->lock);
		}
	printf("%lld %d is eating\n", current_time(phi), phi->id_phi);
	while(phi->curr_mili + phi->timer_eat > current_time(phi))
	pthread_mutex_unlock(&phi->mainstr->fork[phi->id_phi]);
	pthread_mutex_unlock(&phi->mainstr->fork[phi->id_phi + 1]);
	phi->count_phi_eat++;
}

void	brainpower(t_philo *phi)
{
	phi->curr_mili = current_time(phi);
	printf("%lld %d is thinking\n", current_time(phi), phi->id_phi);
	while(phi->curr_mili + phi->timer_eat > current_time(phi));
}

void	*routine(void *arg)
{
	t_philo *phi;
	int i = 0;
	
	phi = (t_philo*)arg;
	while (phi->mainstr->death != 1)
	{
		if (phi->id_phi % 2 != 0)
		{	
			forks_and_food(phi);
			sleepy_philo(phi);
		}
		brainpower(phi);
		i++;
	}	
	return (NULL);
}

int start_simulation(t_mainS *s)
{
	int i;
	pthread_t tid[s->nbr_phi];
	
	i = 0;
	// printf("NBR_phi %d\n", s->nbr_phi);
	// pthread_mutex_init(s->fork, NULL);
	s->death = 0;
	pthread_mutex_init(&s->lock, NULL);
	while (i < s->nbr_fork)
	{
		pthread_mutex_init(&s->fork[i], NULL);
		i++;
	}	
	i = 0;
	while (i < s->nbr_phi)
	{
		if (pthread_create(&tid[i] , NULL, &routine, &s->phi[i]) != 0)
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
	pthread_mutex_destroy(&s->lock);
	while (i < s->nbr_fork)
	{
		pthread_mutex_destroy(&s->fork[i]);	
		i++;
	}	
	return(0);
}