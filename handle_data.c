/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:22:32 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/11/18 19:23:59 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_av(char *str, long nbr)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	if (nbr > 2147483647 || nbr < -2147483648)
		return (1);
	return (0);
}

int	get_arg(int ac, char **av, t_data *data)
{
	if (!check_av(av[1], atol_philo(av[1])))
		data->num_philo = atol_philo(av[1]);
	if (!check_av(av[2], atol_philo(av[2])))
		data->time_to_die = atol_philo(av[2]);
	if (!check_av(av[3], atol_philo(av[3])))
		data->time_to_eat = atol_philo(av[3]);
	if (!check_av(av[4], atol_philo(av[4])))
		data->time_to_sleep = atol_philo(av[4]);
	if (ac == 6)
	{
		if (!check_av(av[5], atol_philo(av[5])))
			data->max_meals = atol_philo(av[5]);
		if (data->max_meals <= 0)
			return (exit_error(12));
	}
	else
		data->max_meals = -1;
	if (data->num_philo <= 0 || data->time_to_die <= 0 || data->time_to_eat <= 0
		|| data->time_to_sleep <= 0)
		return (exit_error(12));
	if (data->num_philo > 500)
		return (exit_error(13));
	return (0);
}

void	increment(t_data *data)
{
	pthread_mutex_lock(&data->full_mtx);
	data->philos_full_count++;
	pthread_mutex_unlock(&data->full_mtx);
}

void	set_value(pthread_mutex_t *mutex, long *dst, long src)
{
	pthread_mutex_lock(mutex);
	*dst = src;
	pthread_mutex_unlock(mutex);
}

long	get_value(pthread_mutex_t *mutex, long *value)
{
	long	result;

	pthread_mutex_lock(mutex);
	result = *value;
	pthread_mutex_unlock(mutex);
	return (result);
}
