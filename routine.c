/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:22:29 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/11/20 17:43:54 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	sim_finish(t_data *data)
{
	if (get_value(&data->finish_mtx, &data->sim_end_flag) == 1)
		return (1);
	return (0);
}

void	write_state(t_state state, t_philo *philo)
{
	long	time_passed;

	pthread_mutex_lock(&philo->data->write_mtx);
	time_passed = get_time(0) - philo->data->sim_start_time;
	if (!sim_finish(philo->data) || state == DIED)
	{
		if (state == TOOK_1ST_FORK || state == TOOK_2ND_FORK)
			printf("%ld %i has taken a fork\n", time_passed, philo->id);
		else if (state == EATING)
			printf(GREEN "%ld %i is eating\n" RESET, time_passed, philo->id);
		else if (state == SLEEPING)
			printf(BLUE "%ld %i is sleeping\n" RESET, time_passed, philo->id);
		else if (state == THINKING)
			printf(YELLOW "%ld %i is thinking\n" RESET, time_passed, philo->id);
		else if (state == DIED)
			printf(RED "%ld %i died\n" RESET, time_passed, philo->id);
	}
	pthread_mutex_unlock(&philo->data->write_mtx);
}

void	multi_routine(t_philo *philo)
{
	pick_fork(philo);
	pthread_mutex_lock(&philo->philo_mtx);
	philo->meals_count++;
	philo->last_meal = get_time(philo->data->sim_start_time);
	pthread_mutex_unlock(&philo->philo_mtx);
	write_state(EATING, philo);
	precise_usleep(philo->data->time_to_eat);
	drop_fork(philo);
	if (philo->meals_count == philo->max_meals)
		increment(philo->data);
	write_state(SLEEPING, philo);
	precise_usleep(philo->data->time_to_sleep);
	write_state(THINKING, philo);
	if ((get_value(&philo->data->data_mtx, &philo->data->num_philo) % 2) != 0
		&& philo->id % 2 == 0)
		precise_usleep(20);
}

void	solo_routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_fork->fork_mtx);
	write_state(TOOK_1ST_FORK, philo);
	precise_usleep(philo->data->time_to_die);
	pthread_mutex_unlock(&philo->left_fork->fork_mtx);
}

void	*routine(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_mtx);
	pthread_mutex_unlock(&philo->data->data_mtx);
	if (philo->data->num_philo > 1 && (philo->id % 2) != 0)
		precise_usleep(20);
	philo->max_meals = get_value(&philo->data->data_mtx,
			&philo->data->max_meals);
	while (!get_value(&philo->data->finish_mtx, &philo->data->sim_end_flag))
	{
		if (philo->data->num_philo == 1)
		{
			solo_routine(philo);
			break ;
		}
		else if (philo->meals_count != philo->max_meals)
			multi_routine(philo);
	}
	return (NULL);
}
