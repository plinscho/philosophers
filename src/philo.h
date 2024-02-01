/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:31:42 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/01 19:18:02 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef PHILO_H
#define PHILO_H

# define L_FORK 1
# define R_FORK 2

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <fcntl.h>
# include <pthread.h>
# include <stdbool.h>
# include <time.h>
# include <stdint.h>

# include <limits.h>
# include <errno.h>

/*
	STRUCTS
*/

typedef struct s_philo
{
	int				id;
	int				num_meals;
	int				l_fork_id;
	int				r_fork_id;
	uint64_t		time_last_meal;
	pthread_t		threat_id;
	struct s_rules	*rules;	
}	t_philo;

typedef struct s_rules
{
	int				philo_units;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				died;
	int				meals;
	int				all_ate;
	uint64_t		start_time;
	pthread_mutex_t	check_meal;
	pthread_mutex_t	printer;
	pthread_mutex_t	forks[250];
	t_philo			philos[250];
}	t_rules;

// ### 	ERROR CODES
typedef enum errors
{
	BAD_INPUT = 1,
	MALLOC = 2,
	MUTEX = 3,
	THREADS = 4,
	TIME = 5,	
	
} error_code;

/*
	UTILS
*/
int			input_check(int argc, char **argv);
int			ph_atoi(char *str);
uint64_t	crono(void);
uint64_t	time_inc(uint64_t past, uint64_t present);

/*
	INITIALIZATION
*/
int		init_mutex(t_rules *rules);
void	init_philo(t_rules *rules);
int		start_simulation(t_rules *rules);

/*
	UTILS
*/
void	print_philo(t_rules *data);
/*
	EXIT_CASES
*/
int		exit_philo(char *input, char *err_msg, error_code err_code);
int		free_struct(t_rules *table);

#endif