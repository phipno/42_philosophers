/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:40:15 by pnolte            #+#    #+#             */
/*   Updated: 2022/10/19 17:25:45 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(int error)
{
	if (error != 0)
	{
		if (error == 100)
			printf("ERROR! To few arguments\n");
		else if (error == 101)
			printf("ERROR! To many arguments\n");
		else if (error == 102)
			printf("ERROR! Protection\n");
		else if (error == 404)
			printf("ERROR! Philos missing\n");
		else if (error == 401)
			printf("ERROR! My programm only eats positive numbers\n");
		else if (error == 403)
			printf("ERROR! To big number\n");
	return(EXIT_FAILURE);
	}
	else
		return(EXIT_SUCCESS);
}

void printS(t_mainS s)
{
	printf("nbr_phi: %d\n", s.nbr_fork);
	printf("nbr_fork: %d\n", s.nbr_fork);
	printf("time_die: %d\n", s.time_die);
	printf("time_eat: %d\n", s.time_eat);
	printf("time_sleep: %d\n", s.time_sleep);
	printf("nbr_times_phi_eat: %d\n", s.nbr_times_phi_eat);
	printf("second: %ld       microseconds: %d\n", s.time.tv_sec, s.time.tv_usec);
	printf("millisec: %lld\n", s.startTime_mili);
}

int start_simulation(t_mainS *s)
{
	int i;
	pthread_t tid[s->nbr_phi];
	
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
	return(0);
}

void freeee(t_mainS *s)
{
	int i;
	
	i = 0;
	while (i < s->nbr_phi)
	{
		free(s->phi);
		i++;
	}
	pthread_mutex_destroy(&s->lock);
	i = 0;
	while (i < s->nbr_fork)
	{
		pthread_mutex_destroy(&s->fork[i]);	
		i++;
	}	
}

int main(int argc, char **argv)
{
	t_mainS s;
	
	s.error = 0;
	if (argc < 5)
		s.error = 100;
	if (argc > 6)
		s.error = 101;
	if (ft_error(s.error) == EXIT_FAILURE)
		return(EXIT_FAILURE);
	s.c_argc = argc;
	if (init_struct(&s, argv) != 0)
		return(ft_error(s.error));
	// printS(s);
	start_simulation(&s);
	freeee(&s);
	return(ft_error(s.error));
}