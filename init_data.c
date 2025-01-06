/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:22:22 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/11/20 13:12:25 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_data_mtx(t_data *data)
{
	pthread_mutex_init(&data->data_mtx, NULL);
	pthread_mutex_init(&data->write_mtx, NULL);
	pthread_mutex_init(&data->full_mtx, NULL);
	pthread_mutex_init(&data->finish_mtx, NULL);
	pthread_mutex_init(&data->start_mtx, NULL);
}

void	init_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philo)
	{
		pthread_mutex_init(&data->forks[i].fork_mtx, NULL);
		data->forks[i].id = i;
		i++;
	}
}

void	init_philo(t_data *data)
{
	t_philo	*philo;
	int		i;

	i = 0;
	while (i < data->num_philo)
	{
		philo = &data->array_philo[i];
		philo->id = i + 1;
		philo->data = data;
		pthread_mutex_init(&philo->philo_mtx, NULL);
		philo->left_fork = &data->forks[i];
		if (philo->id == 1)
			philo->right_fork = &data->forks[philo->data->num_philo - 1];
		else
			philo->right_fork = &data->forks[(i - 1)];
		i++;
	}
}

int	init_threads(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = data->array_philo;
	i = 0;
	while (i < data->num_philo)
	{
		if (pthread_create(&philo[i].thread, NULL, (void *)routine,
				&philo[i]) != 0)
			return (1);
		i++;
	}
	return (0);
}

int	init_data(t_data *data)
{
	init_data_mtx(data);
	init_forks(data);
	init_philo(data);
	pthread_mutex_lock(&data->data_mtx);
	if (init_threads(data) != 0)
		return (1);
	return (0);
}
