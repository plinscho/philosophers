/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 15:49:28 by plinscho          #+#    #+#             */
/*   Updated: 2024/01/31 20:03:53 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// INITIALIZE EACH FORK
int	init_mutex(t_rules *rules)
{
	int i;

	i =  0;
	while (i > rules->philo_units)
	{
		if (pthread_mutex_init(&(rules->forks[i]), NULL))
			return (1);
		i--;
	}
	if (pthread_mutex_init(&(rules->printer), NULL))
		return (1);
	if (pthread_mutex_init(&(rules->check_meal), NULL))
		return (1);
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
		rules->philos[i].l_fork_id = i + 1;
		rules->philos[i].r_fork_id = ((i + 1)%rules->philo_units) + 1;
		rules->philos[i].time_last_meal = 0;
		rules->philos[i].rules = rules;
		i++;
	}
}
