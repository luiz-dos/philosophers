/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:22:10 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/11/18 18:38:09 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;

	memset(&data, 0, sizeof(data));
	if (ac < 5 || ac > 6)
		return (exit_error(1));
	if (get_arg(ac, av, &data) != 0)
		return (1);
	if (init_data(&data))
	{
		clear_sim(&data);
		return (1);
	}
	data.sim_start_time = get_time(0);
	pthread_mutex_unlock(&data.data_mtx);
	monitoring(&data);
	clear_sim(&data);
	printf(CYAN "End of simulation\n" RESET);
	return (0);
}
