/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:29:09 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/11/20 13:12:14 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	exit_error(int error_code)
{
	if (error_code == 1)
		printf(RED "Error: Incorrect number of arguments.\n" RESET
			"Please write ./philo "
			"1 2 3 4 *5\n1.number_of_philosophers\n2.time_to_die(in ms)\n"
			"3.time_to_eat(in ms)\n4.time_to_sleep (in ms)\n(*Optional)\n5."
			"number_of_times_each_philosopher_must_eat\n");
	if (error_code == 12)
		printf(RED "Error: "RESET"Invalid arguments\n");
	if (error_code == 13)
		printf(GREEN "Please don't put so many philosophers\n" RESET);
	if (error_code == 14)
		printf(RED "Error: "RESET"Problem using the function gettimeofday.\n");
	return (error_code);
}
