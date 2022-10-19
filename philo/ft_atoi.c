/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pnolte <pnolte@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 14:50:13 by pnolte            #+#    #+#             */
/*   Updated: 2022/10/19 17:55:31 by pnolte           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	checker_for_atoi(char *str, t_mainS *s)
{
	int	i;

	i = 0;
	if (str[i + 1] == '\0' && (str[i] == '-' || str[i] == '+'))
		s->error = 401;
	if (str[i] == '-' || str[i] == '+' || (str[i] <= '9' && str[i] >= '0'))
		i++;
	if (i == 0)
		s->error = 401;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			s->error = 401;
		i++;
	}
}

static void	norminette(int *index, t_mainS *s)
{
	s->error = 401;
	index++;
}

int	ft_atoi(char *str, t_mainS *s)
{
	long int	res;
	int			index;
	int			sign;

	sign = 1;
	index = 0;
	checker_for_atoi(str, s);
	if (str[index] == '+')
		index++;
	if (str[index] == '-')
		norminette(&index, s);
	res = 0;
	while (str[index] != '\0' && str[index] >= '0' && str[index] <= '9')
	{
		res = res * 10 + str[index] - '0';
		index++;
	}
	if (res > 2147483647)
	{
		s->error = 403;
		return (0);
	}
	else
		return (res * sign);
}
