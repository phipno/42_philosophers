/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 15:56:58 by pnolte            #+#    #+#             */
/*   Updated: 2022/10/19 17:55:53 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	death_manager(int time_left, t_philo *phi)
{
	if (time_left >= phi->timer_die)
	{
		pthread_mutex_lock(&phi->slk->lock);
		if (phi->slk->death != true)
		{
			phi->curr_run_mili = current_runtime(phi);
			printf("%lld %d died\n", phi->curr_run_mili, phi->id);
			phi->slk->death = true;
			pthread_mutex_unlock(&phi->slk->lock);
			return (true);
		}
		pthread_mutex_unlock(&phi->slk->lock);
	}
	return (false);
}

void	print_manager(char action, t_philo *phi)
{
	pthread_mutex_lock(&phi->slk->lock);
	if (phi->slk->death == false)
	{
		if (action == 'e')
			printf("%lld %d is eating\n", phi->curr_run_mili, phi->id);
		else if (action == 'f')
			printf("%lld %d has taken a fork\n", phi->curr_run_mili, phi->id);
		else if (action == 's')
			printf("%lld %d is sleeping\n", phi->curr_run_mili, phi->id);
		else if (action == 't')
			printf("%lld %d is thinking\n", phi->curr_run_mili, phi->id);
	}
	pthread_mutex_unlock(&phi->slk->lock);
}

long long	current_runtime(t_philo *phi)
{
	struct timeval	curr;
	long long		ms;

	if (gettimeofday(&curr, NULL) != 0)
		phi->error = 102;
	ms = ((curr.tv_sec * 1000) + (curr.tv_usec / 1000)) - phi->start_time_mili;
	return (ms);
}

void	my_sleep(long long ms, t_philo *phi)
{
	long long	stop;

	stop = current_runtime(phi) + ms;
	if (ms > 6)
	{
		usleep((ms - 6) * 1000);
		while (stop > current_runtime(phi))
			;
	}
	else
	{
		while (stop > current_runtime(phi))
			usleep(50);
	}
}
