/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:31:42 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/07 19:21:30 by plinscho         ###   ########.fr       */
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

#define FORK "has taken a fork"
#define EAT "is eating"
#define SLEEP "is sleeping"
#define THINK "is thinking"
#define DIE "has died"

/*
	STRUCTS
*/

typedef struct s_philo
{
	int				id;
	int				num_meals;
	pthread_t		threat_id;
	pthread_mutex_t	m_death;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	struct s_rules	*rules;	
	int				done_eating;
	uint64_t		time_last_meal;
	uint64_t		time_to_die;
}	t_philo;

typedef struct s_rules
{
	int				philo_units;
	uint64_t		time_to_die;
	uint64_t		time_to_eat;
	uint64_t		time_to_sleep;
	int				died;
	int				max_meals;
	int				all_ate;
	uint64_t		start_time;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	m_check_meal;
	pthread_mutex_t	m_printer;
	pthread_mutex_t	m_dead;
	t_philo			*philos;
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

// COLOR CODES
# define E "\033[m"        //end
# define R "\033[1;31m"    //red
# define G "\033[1;32m"    //green
# define Y "\033[1;33m"    //yellow
# define B "\033[1;34m"    //blue
# define T "\033[1;35m"	   //Turquesa
# define C "\033[1;36m"    //Cyan
# define O "\033[38;5;208m" //orange
# define F "\033[38;5;128m"  //purple

// ROUTINE
void	simul(t_philo *ph);
void	check_philos(t_rules *rules);

// UTILS
int			input_check(int argc, char **argv);
int			ph_atoi(char *str);
uint64_t	crono(void);
void		ph_print(char *color, t_philo *philo, char *s, bool dead);

//	INITIALIZATION
int		init_struct_mutex(int argc, char **argv, t_rules *rules);
int		init_simulation(t_rules *rules);

/*
	UTILS
*/
void	print_philo(t_rules *data);
void	ft_usleep(uint64_t ms_wait);
/*
	EXIT_CASES
*/
int		exit_philo(char *input, char *err_msg, error_code err_code);
int		free_struct(t_rules *table);

#endif