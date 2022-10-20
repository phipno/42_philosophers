/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:44:07 by pnolte            #+#    #+#             */
/*   Updated: 2022/10/20 16:56:39 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_them_mutexes(t_philo *phi)
{
	if (phi->id % 2 == 0)
	{
		pthread_mutex_lock(&phi->slk->fork[phi->id - 1]);
		print_manager('f', phi);
		pthread_mutex_lock(&phi->slk->fork[phi->id]);
		print_manager('f', phi);
	}
	else if (phi->id != phi->nbr_phi && phi->id % 2 != 0)
	{
		pthread_mutex_lock(&phi->slk->fork[phi->id]);
		print_manager('f', phi);
		pthread_mutex_lock(&phi->slk->fork[phi->id - 1]);
		print_manager('f', phi);
	}
	else if (phi->id == phi->nbr_phi && phi->nbr_phi % 2 != 0)
	{
		pthread_mutex_lock(&phi->slk->fork[0]);
		print_manager('f', phi);
		pthread_mutex_lock(&phi->slk->fork[phi->id - 1]);
		print_manager('f', phi);
	}
}

void	unlock_them_mutexes(t_philo *phi)
{
	if (phi->id % 2 == 0)
	{
		pthread_mutex_unlock(&phi->slk->fork[phi->id - 1]);
		print_manager('f', phi);
		pthread_mutex_unlock(&phi->slk->fork[phi->id]);
		print_manager('f', phi);
	}
	else if (phi->id != phi->nbr_phi && phi->id % 2 != 0)
	{
		pthread_mutex_unlock(&phi->slk->fork[phi->id]);
		print_manager('f', phi);
		pthread_mutex_unlock(&phi->slk->fork[phi->id - 1]);
		print_manager('f', phi);
	}
	else if (phi->id == phi->nbr_phi && phi->nbr_phi % 2 != 0)
	{
		pthread_mutex_unlock(&phi->slk->fork[0]);
		print_manager('f', phi);
		pthread_mutex_unlock(&phi->slk->fork[phi->id - 1]);
		print_manager('f', phi);
	}
}