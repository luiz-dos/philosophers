/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 12:12:33 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/11/18 18:48:52 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

/* impar */
void	pick_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_lock(&philo->right_fork->fork_mtx);
		write_state(TOOK_1ST_FORK, philo);
		pthread_mutex_lock(&philo->left_fork->fork_mtx);
		write_state(TOOK_2ND_FORK, philo);
	}
	else
	{
		pthread_mutex_lock(&philo->left_fork->fork_mtx);
		write_state(TOOK_2ND_FORK, philo);
		pthread_mutex_lock(&philo->right_fork->fork_mtx);
		write_state(TOOK_1ST_FORK, philo);
	}
}

void	drop_fork(t_philo *philo)
{
	if (philo->id % 2 != 0)
	{
		pthread_mutex_unlock(&philo->right_fork->fork_mtx);
		pthread_mutex_unlock(&philo->left_fork->fork_mtx);
	}
	else
	{
		pthread_mutex_unlock(&philo->left_fork->fork_mtx);
		pthread_mutex_unlock(&philo->right_fork->fork_mtx);
	}
}
