/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:42:06 by pnolte            #+#    #+#             */
/*   Updated: 2022/10/20 16:46:28 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo
{
	int				error;
	int				id;
	int				timer_die;
	int				timer_eat;
	int				timer_sleep;
	int				count_phi_eat;
	int				nbr_phi;
	int				multi;
	long long		curr_run_mili;
	long long		start_time_mili;
	struct s_mainS	*slk;
}		t_philo;

typedef struct s_mainS
{
	t_philo			*phi;
	int				id;
	int				error;
	int				c_argc;
	int				nbr_phi;
	int				nbr_fork;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_times_phi_eat;
	bool			death;
	pthread_mutex_t	*fork;
	pthread_mutex_t	lock;
	struct timeval	time;
	long long		starttime_mili;
}		t_mainS;

int			ft_atoi(char *str, t_mainS *s);
int			init_struct(t_mainS *s, char **argv);
t_philo		*init_each_philo(t_mainS *s);
long long	transform_milli(t_mainS *s);
int			start_simulation(t_mainS *s);
void		*routine(void *arg);
void		print_manager(char action, t_philo *phi);
bool		death_manager(int time_left, t_philo *phi);
void		my_sleep(long long ms, t_philo *phi);
long long	current_runtime(t_philo *phi);
void		lock_them_mutexes(t_philo *phi);
void		unlock_them_mutexes(t_philo *phi);

#endif