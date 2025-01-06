/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luiz-dos <luiz-dos@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 12:22:41 by luiz-dos          #+#    #+#             */
/*   Updated: 2024/11/20 17:26:55 by luiz-dos         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

/* colors */
# define RED "\033[1;31m"
# define GREEN "\033[1;32m"
# define YELLOW "\033[1;33m"
# define BLUE "\033[1;34m"
# define CYAN "\033[1;36m"
# define RESET "\033[0m"

/* fork structure */
typedef struct s_fork
{
	pthread_mutex_t		fork_mtx;
	int					id;
}						t_fork;

/* declaring the structure to avoid error */
typedef struct s_data	t_data;

/* philosopher's data */
typedef struct s_philo
{
	int					id;
	long				meals_count;
	long				max_meals;
	long				last_meal;
	long				is_satisfied;
	long				died;
	t_data				*data;
	pthread_mutex_t		philo_mtx;
	t_fork				*left_fork;
	t_fork				*right_fork;
	pthread_t			thread;
}						t_philo;

/* all data */
typedef struct s_data
{
	long				num_philo;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				max_meals;
	long				philos_full_count;
	long				sim_end_flag;
	long				sim_start_time;
	pthread_mutex_t		data_mtx;
	pthread_mutex_t		write_mtx;
	pthread_mutex_t		full_mtx;
	pthread_mutex_t		finish_mtx;
	pthread_mutex_t		start_mtx;
	t_fork				forks[500];
	t_philo				array_philo[500];
}						t_data;

/* named constants */
typedef enum e_state
{
	EATING,
	SLEEPING,
	THINKING,
	TOOK_1ST_FORK,
	TOOK_2ND_FORK,
	DIED,
	INIT,
	LOCK,
	UNLOCK,
	DESTROY,
	CREATE,
	JOIN
}						t_state;

/* init functions */
int						main(int ac, char **av);
int						get_arg(int ac, char **av, t_data *data);
int						init_data(t_data *data);
void					init_data_mtx(t_data *data);
void					init_forks(t_data *data);
void					init_philo(t_data *data);
int						init_threads(t_data *data);

/* handle error*/
int						exit_error(int error_code);

/* utils */
long					atol_philo(char *n);
long					get_value(pthread_mutex_t *mutex, long *value);
void					set_value(pthread_mutex_t *mutex, long *dst, long src);
void					increment(t_data *data);

/* time */
void					precise_usleep(long time);
long					get_time(long start);

/* routine */
void					*routine(t_philo *philo);
void					solo_routine(t_philo *philo);
void					multi_routine(t_philo *philo);
void					write_state(t_state state, t_philo *philo);
int						sim_finish(t_data *data);
void					pick_fork(t_philo *philo);
void					drop_fork(t_philo *philo);

/* monitoring */
void					monitoring(t_data *data);

/* clear simulation */
void					clear_sim(t_data *data);

#endif /* PHILOSOPHERS_H */