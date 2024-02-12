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

void	check_death(t_philo p, t_rules *rules)
{
	pthread_mutex_lock(&rules->m_dead);
	if (crono() - p.time_last_meal > rules->time_to_die)
	{
		rules->died = 1;
		pthread_mutex_unlock(&rules->m_dead);
		ph_print(R, &p, DIE, true);
	}
	else
		pthread_mutex_unlock(&rules->m_dead);
}

void	check_philos(t_rules *rules)
{
	int			i;
	int			ph_done;

	i = 0;
	ph_done = 0;
	while (rules->died == 0)
	{
		check_death(rules->philos[i], rules);
		pthread_mutex_lock(&rules->philos[i].m_death);
		if (rules->philos[i].done_eating)
			ph_done++;
		pthread_mutex_unlock(&rules->philos[i].m_death);
		if (ph_done == rules->philo_units)
			break;
		i++;
		if (i == rules->philo_units)
			i = 0;
	}
}

void	take_fork(t_philo *ph)
{
	if (ph->id == 1)
	{
		pthread_mutex_lock(ph->r_fork);
		ph_print(T, ph, FORK, false);
		pthread_mutex_lock(ph->l_fork);
	}
	else
	{
		pthread_mutex_lock(ph->l_fork);
		ph_print(T, ph, FORK, false);
		pthread_mutex_lock(ph->r_fork);
	}
	ph_print(C, ph, FORK, false);
}

void	ph_life(t_philo *ph)
{
	take_fork(ph);
	ph_print(G, ph, EAT, false);
	pthread_mutex_lock(&ph->m_death);
	ph->time_last_meal = crono();
	ph->num_meals += 1;
	if (ph->num_meals == ph->rules->max_meals)
		ph->done_eating++;
	pthread_mutex_unlock(&ph->m_death);
	ft_usleep(ph->rules->time_to_eat);
	pthread_mutex_unlock(ph->r_fork);
	pthread_mutex_unlock(ph->l_fork);
	ph_print(Y, ph, SLEEP, false);
	ft_usleep(ph->rules->time_to_sleep);
	ph_print(F, ph, THINK, false);
}

void	simul(t_philo *ph)
{
	int	exit;

	if (ph->id % 2 != 0)
		ft_usleep(ph->rules->time_to_eat);
	exit = 0;
	while (exit == 0 && ph->done_eating == 0)
	{
		ph_life(ph);
		pthread_mutex_lock(&ph->rules->m_dead);
		exit = ph->rules->died;
		pthread_mutex_unlock(&ph->rules->m_dead);
	}
}
