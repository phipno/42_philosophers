/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 16:44:07 by pnolte            #+#    #+#             */
/*   Updated: 2022/10/20 18:56:55 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_them_mutexes(t_philo *phi)
{
	if (phi->nbr_phi % 2 == 0)
		pthread_mutex_lock(&phi->slk->fork[phi->id - 1]);
	else if (phi->id != phi->nbr_phi && phi->nbr_phi % 2 != 0)
		pthread_mutex_lock(&phi->slk->fork[phi->id]);
	print_manager('f', phi);
	if (phi->id == phi->nbr_phi && phi->nbr_phi % 2 != 0)
		pthread_mutex_lock(&phi->slk->fork[0]);
	else if (phi->id == phi->nbr_phi && phi->nbr_phi % 2 == 0)
		pthread_mutex_lock(&phi->slk->fork[0]);
	else if (phi->nbr_phi % 2 == 0 && phi->id != phi->nbr_phi)
		pthread_mutex_lock(&phi->slk->fork[phi->id]);
	else
		pthread_mutex_lock(&phi->slk->fork[phi->id - 1]);
	print_manager('f', phi);
}

void	unlock_them_mutexes(t_philo *phi)
{	
	if (phi->nbr_phi % 2 == 0)
		pthread_mutex_unlock(&phi->slk->fork[phi->id - 1]);
	else if (phi->id != phi->nbr_phi && phi->nbr_phi % 2 != 0)
		pthread_mutex_unlock(&phi->slk->fork[phi->id]);
	if (phi->id == phi->nbr_phi && phi->nbr_phi % 2 != 0)
		pthread_mutex_unlock(&phi->slk->fork[0]);
	else if (phi->id == phi->nbr_phi && phi->nbr_phi % 2 == 0)
		pthread_mutex_unlock(&phi->slk->fork[0]);
	else if (phi->nbr_phi % 2 == 0 && phi->id != phi->nbr_phi)
		pthread_mutex_unlock(&phi->slk->fork[phi->id]);
	else
		pthread_mutex_unlock(&phi->slk->fork[phi->id - 1]);
}
