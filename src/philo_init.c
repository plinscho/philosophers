/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:49:28 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/12 17:18:13 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_rules *rules)
{
	int	i;

	i = rules->philo_units;
	while (--i >= 0)
	{
		rules->philos[i].id = i;
		rules->philos[i].num_meals = 0;
		rules->philos[i].l_fork = i;
		rules->philos[i].r_fork = (i + 1) % rules->philo_units;
		rules->philos[i].time_last_meal = 0;
		rules->philos[i].rules = rules;
	}

}

int	init_mutex(t_rules *r)
{
	int	i;

	i = r->philo_units;
	while (i >= 0)
	{
		if (pthread_mutex_init(&(r->forks[i]), NULL))
			return (exit_philo("INIT_MUTEX", "Mutex fail to initialize", THREADS));
		i--;
	} 
	if (pthread_mutex_init(&(r->m_check_meal), NULL))
		return (exit_philo("INIT_MUTEX", "Mutex fail to initialize", THREADS));
	if (pthread_mutex_init(&(r->m_printer), NULL))
		return (exit_philo("INIT_MUTEX", "Mutex fail to initialize", THREADS));
	if (pthread_mutex_init(&(r->m_dead), NULL))
		return (exit_philo("INIT_MUTEX", "Mutex fail to initialize", THREADS));
	return (0);
}

//	argc:		0			1					2			3				4		
// input is [./philo] [number of philos] [time to die] [time_to_eat] [time_to_sleep] [(5)]
int	init_struct_mutex(int argc, char **argv, t_rules *rules)
{
	rules->philo_units = (uint64_t)ph_atoi(argv[1]);
	rules->time_to_die = (uint64_t)ph_atoi(argv[2]);
	rules->time_to_eat = (uint64_t)ph_atoi(argv[3]);
	rules->time_to_sleep = (uint64_t)ph_atoi(argv[4]);
	rules->max_meals = -1;	// value if no additional option
	rules->died = 0;
	rules->all_ate = 0;
	if (argc > 5)
		rules->max_meals = (uint64_t)ph_atoi(argv[5]);
	if (rules->philo_units == 0)
		return (exit_philo("INPUT", "At least 1 philo has to exist...\n", BAD_INPUT));
	else if (rules->philo_units > 250)
		return (exit_philo("THREADS", "Too many threads!", THREADS));
	if (init_mutex(rules))
		return (THREADS);
	init_philo(rules);
	return (0);	
}
