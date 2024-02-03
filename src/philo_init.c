/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:49:28 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/03 20:31:46 by plinscho         ###   ########.fr       */
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
		if (pthread_create(&(ph[i].threat_id), NULL, (void *)simul, \
		&(rules->philos[i])))
			return (THREADS);
		i++;
	}
	return (0);
}

void	init_philo(t_rules *rules)
{
	int	i;

	i = 0;
	while (i < rules->philo_units)
	{
		rules->philos[i].id = i + 1;
		rules->philos[i].num_meals = 0;
		if (i == 0)
			rules->philos[i].r_fork = rules->philos[rules->philo_units - 1].l_fork;
		else
			rules->philos[i].r_fork = rules->philos[i - 1].l_fork;
//		pthread_mutex_init(&rules->philos[i].l_fork, NULL);
		rules->philos[i].time_last_meal = 0;
		rules->philos[i].rules = rules;
		i++;
	}
}

//	argc:		0			1					2			3				4		
// input is [./philo] [number of philos] [time to die] [time_to_eat] [time_to_sleep] [(5)]
int	init_struct_mutex(int argc, char **argv, t_rules *rules)
{
	rules->philos = (t_philo *)malloc(sizeof(t_philo) * rules->philo_units);
	if (rules->philos == NULL)
		return (exit_philo("MALLOC", "Malloc failed.\n", MALLOC));
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
	else if (rules->philo_units > 200)
		return (exit_philo("THREADS", "Too many threads!", THREADS));
	pthread_mutex_init(&rules->m_check_meal, NULL);
	pthread_mutex_init(&rules->m_printer, NULL);
	init_philo(rules);
	return (0);	
}

