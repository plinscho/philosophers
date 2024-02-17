/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:49:28 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/17 18:26:33 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_simulation(t_rules *rules)
{
	t_philo	*ph;
	int		i;

	i = 0;
	ph = rules->philos;
	rules->start_time = crono();
	while (i < rules->philo_units)
	{
		pthread_create(&(ph[i].threat_id), NULL, sim, &(rules->philos[i]));
		i++;
	}
	return (0);
}

void	init_philo(t_rules *rules)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(rules->m_start));
	while (i < rules->philo_units)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].rules = rules;
		rules->philos[i].time_die= rules->time_to_die;
		rules->philos[i].num_meals = 0;
		if (i == 0)
			rules->philos[i].r_fork = 
			&(rules->philos[rules->philo_units - 1].l_fork);
		else
			rules->philos[i].r_fork = &(rules->philos[i - 1].l_fork);
		pthread_mutex_init(&rules->philos[i].l_fork, NULL);
		pthread_mutex_init(&rules->philos[i].m_check_meal, NULL);
		i++;
	}
}

int	init_mutex(t_rules *r)
{
	if (pthread_mutex_init(&(r->m_start), NULL))
		return (exit_philo("INIT_MUTEX", "Mutex start failed", THREADS));
	if (pthread_mutex_init(&(r->m_printer), NULL))
		return (exit_philo("INIT_MUTEX", "Mutex print failed", THREADS));
	if (pthread_mutex_init(&(r->m_dead), NULL))
		return (exit_philo("INIT_MUTEX", "Mutex death failed", THREADS));
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
	rules->max_meals = -1;
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
	init_simulation(rules);
	return (0);	
}
