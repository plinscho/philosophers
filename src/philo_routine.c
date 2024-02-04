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

void	check_death(t_philo p, t_rules *rules, uint64_t death_time)
{
	pthread_mutex_lock(&rules->m_dead);
	if (crono() - rules->start_time > death_time)
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
	uint64_t	time;
	int			i;
	int			ph_done;

	i = 0;
	ph_done = 0;
	while (rules->died == 0)
	{
		pthread_mutex_lock(&rules->m_check_meal);
		time = rules->philos[i].time_to_die;
		pthread_mutex_unlock(&rules->m_check_meal);
		check_death(rules->philos[i], rules, time);
		pthread_mutex_lock(&rules->m_check_meal);
		if (rules->philos[i].num_meals == rules->max_meals)
		{
			rules->philos[i].done_eating = 1;
			ph_done++;
		}
		pthread_mutex_unlock(&rules->m_check_meal);
		if (ph_done == rules->philo_units)
			break;

	}
}

void	ph_life(t_philo *ph)
{
	pthread_mutex_lock(&ph->l_fork);
	ph_print(T, ph, FORK, false);
	pthread_mutex_lock(&ph->r_fork);
	ph_print(C, ph, FORK, false);
	pthread_mutex_lock(&ph->rules->m_check_meal);
	ph->time_to_die += (crono() - ph->rules->time_to_die);
	ph->num_meals++;
	if (ph->num_meals == ph->rules->max_meals)
		ph->done_eating++;
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
	while (exit == 0 && ph->done_eating == 0)
	{
		ph_life(ph);
		pthread_mutex_lock(&ph->rules->m_dead);
		exit = ph->rules->died;
		pthread_mutex_unlock(&ph->rules->m_dead);
	}
}
