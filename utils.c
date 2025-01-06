/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:13:07 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/11/20 15:41:27 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long	get_time(long start)
{
	struct timeval	time_val;

	gettimeofday(&time_val, NULL);
	return (((time_val.tv_sec * 1000) + (time_val.tv_usec / 1000)) - start);
}

void	precise_usleep(long time)
{
	long	target_time;

	target_time = get_time(0) + time;
	while (get_time(0) < target_time)
		usleep(100);
}

long	atol_philo(char *n)
{
	int		i;
	int		signal;
	long	result;

	i = 0;
	signal = 1;
	while (n[i] == ' ' || (n[i] >= 9 && n[i] <= 13))
		i++;
	if (n[i] == '-' || n[i] == '+')
	{
		if (n[i] == '-')
			signal = -1;
		i++;
	}
	result = 0;
	while (n[i] >= '0' && n[i] <= '9')
		result = result * 10 + (n[i++] - '0');
	return (result * signal);
}
