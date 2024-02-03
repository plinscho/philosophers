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

#include "philo.h"

void	check_philos(t_rules *rules)
{
	(void)rules;
}

void	ph_eat(t_philo *ph)
{
	pthread_mutex_lock(&ph->l_fork);
	ph_print(T, ph, FORK, false);
	pthread_mutex_lock(&ph->r_fork);
	ph_print(C, ph, FORK, false);
	pthread_mutex_lock(&ph->rules->m_check_meal);
	ph->time_to_die += crono() - ph->rules->start_time;
	ph->num_meals++;
	pthread_mutex_unlock(&ph->rules->m_check_meal);
	ph_print(G, ph, EAT, false);
	ft_usleep(ph->rules->time_to_eat);
	pthread_mutex_unlock(&ph->l_fork);
	pthread_mutex_unlock(&ph->r_fork);
	ph_print(Y, ph, SLEEP, false);
	ft_usleep(ph->rules->time_to_sleep);
	ph_print(F, ph, THINK, false);
}

void	simul(t_philo *ph)
{
	int	exit;

	if (ph->id % 2 == 0)
		ft_usleep(ph->rules->time_to_eat);
	exit = 0;
	while (exit == 0 || ph->num_meals != ph->rules->max_meals)
	{
		ph_eat(ph);
		pthread_mutex_lock(&ph->rules->m_dead);
		exit = ph->rules->died;
		pthread_mutex_unlock(&ph->rules->m_dead);
	}
}
