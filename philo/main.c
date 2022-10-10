/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:40:15 by pnolte            #+#    #+#             */
/*   Updated: 2022/10/05 17:22:37 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(int error)
{
	if (error != 0)
	{
		if (error == 100)
			printf("ERROR! To few arguments");
		else if (error == 101)
			printf("ERROR! To many arguments");
		else if (error == 102)
			printf("ERROR! Protection");
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
	printf("seconds : %ld\nmicro seconds : %d", s.start_time.tv_sec, s.start_time.tv_usec);
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
	return(ft_error(s.error));
}