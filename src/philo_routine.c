/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_cycle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 16:36:30 by plinscho          #+#    #+#             */
/*   Updated: 2024/01/31 20:06:36 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/*
	It shall be safe to destroy an initialized mutex that is unlocked.
	Attempting to destroy a locked mutex results in undefined behavior.
*/

#include "philo.h"

void	simul(void *philo)
{
	
}

int	start_simulation(t_rules *rules)
{
	t_philo	*ph;
	int		i;

	i = 0;
	ph = rules->philos;
	while (i < rules->philo_units)
	{
		if (pthread_create(&(ph[i].threat_id), NULL, (void *)simul, &(ph[i])))
			return (THREADS);
		ph[i].time_last_meal = crono();
		if (ph[i].time_last_meal == 0)
			return (TIME);
		i++;
	}
}