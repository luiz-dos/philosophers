/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_sim.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:22:16 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/11/18 19:08:28 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	clear_sim(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
		pthread_join(data->array_philo[i++].thread, NULL);
	i = 0;
	while (i < data->num_philo)
		pthread_mutex_destroy(&data->forks[i++].fork_mtx);
	pthread_mutex_destroy(&data->data_mtx);
	pthread_mutex_destroy(&data->write_mtx);
	pthread_mutex_destroy(&data->finish_mtx);
	pthread_mutex_destroy(&data->full_mtx);
	pthread_mutex_destroy(&data->start_mtx);
}
