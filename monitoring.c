/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:22:26 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/11/20 17:35:51 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	monitoring(t_data *data)
{
	int		i;
	long	last_meal;
	long	elapsed;
	t_philo	*philo;

	i = 0;
	while (1)
	{
		philo = &data->array_philo[i];
		last_meal = get_value(&philo->philo_mtx, &philo->last_meal);
		elapsed = get_time(data->sim_start_time) - last_meal;
		if (elapsed > data->time_to_die)
		{
			set_value(&data->finish_mtx, &philo->data->sim_end_flag, 1);
			write_state(DIED, philo);
			break ;
		}
		if (get_value(&data->full_mtx,
				&data->philos_full_count) == philo->data->num_philo)
		{
			set_value(&data->finish_mtx, &data->sim_end_flag, 1);
			break ;
		}
		i = (i + 1) % data->num_philo;
	}
}
