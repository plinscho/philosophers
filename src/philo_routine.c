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

void	is_dead(t_rules *rules, int i, uint64_t time)
{
	pthread_mutex_lock(&(rules->m_dead));
	if (crono() - rules->start_time > time)
	{
		rules->died = 1;
		pthread_mutex_unlock(&(rules->m_dead));
		ph_print(R, &(rules->philos[i]), DIE, true);
	}
	else
		pthread_mutex_lock(&(rules->m_dead));
}

void	check_philos(t_rules *rules)
{
	uint64_t	time;
	int			i;

	i = 0;
	while (rules->died == 0)
	{
		pthread_mutex_lock(&(rules->philos[i].m_check_meal));
		time = rules->philos[i].time_last_meal;
		pthread_mutex_unlock(&(rules->philos[i].m_check_meal));
		is_dead(rules, i, time);
		pthread_mutex_lock(&(rules->philos[i].m_check_meal));
		if (rules->philos[i].num_meals == rules->max_meals)
			rules->all_ate++;
		pthread_mutex_unlock(&(rules->philos[i].m_check_meal));
		if (rules->philo_units == rules->all_ate)
			break ;
		i++;
		if (i == rules->philo_units)
		{
			i = 0;
			rules->all_ate = 0;
		}
	}
}

void	ph_life(t_philo *ph)
{
	t_rules	*rules;

	rules = ph->rules;
	pthread_mutex_lock(&(ph->l_fork));
	ph_print(F, ph, FORK, false);
	if (rules->philo_units == 1)
	{
		ft_usleep(rules->time_to_die);
		pthread_mutex_unlock(&(ph->l_fork));
		return ;
	}
	pthread_mutex_lock(ph->r_fork);
	ph_print(B, ph, FORK, false);
	pthread_mutex_lock(&(ph->m_check_meal));
	ph->time_die = rules->time_to_die + (crono() - rules->time_to_die);
	ph->num_meals++;
	pthread_mutex_unlock(&(ph->m_check_meal));
	ph_print(G, ph, EAT, false);
	ft_usleep(rules->time_to_eat);
	pthread_mutex_unlock(&(ph->l_fork));
	pthread_mutex_unlock(ph->r_fork);
	ph_print(Y, ph, SLEEP, false);
	ft_usleep(rules->time_to_sleep);
	ph_print(T, ph, THINK, false);
}

void	*sim(void *void_ph)
{
	int		finish;
	t_rules	*rules;
	t_philo	*philo;

	philo = (t_philo *)void_ph;
	rules = philo->rules;
	finish = 0;
	if (philo->id % 2 == 0)
		ft_usleep(philo->rules->time_to_eat);
	while (!finish && (philo->num_meals != philo->rules->max_meals))
	{
		ph_life(philo);
		pthread_mutex_lock(&(rules->m_dead));
		finish = rules->died;
		pthread_mutex_unlock(&(rules->m_dead));	
	}
	return (NULL);
}
