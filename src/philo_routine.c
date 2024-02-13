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

void	check_death(t_rules *rules, t_philo *p)
{
	int	i;

	while (rules->all_ate == 0)
	{
		i = -1;
		while (++i < rules->philo_units && rules->died == 0)
		{
			pthread_mutex_lock(&(rules->m_dead));
			if ((crono() - p[i].time_last_meal) > rules->time_to_die)
			{
				ph_print(R, &p[i], DIE, true);
				rules->died = 1;
				pthread_mutex_unlock(&(rules->m_dead));
				return ;
			}
			pthread_mutex_unlock(&(rules->m_dead));
			usleep(50);
		}
		i = 0;
		while (rules->max_meals != -1 && i < rules->philo_units && 
				p[i].num_meals >= rules->max_meals)
			i++;
		if (i == rules->philo_units)
			rules->all_ate = 1;
	}
}

void	ph_life(t_philo *ph)
{
	t_rules	*rules;

	rules = ph->rules;
	pthread_mutex_lock(&(rules->forks[ph->l_fork]));
	ph_print(F, ph, FORK, false);
	pthread_mutex_lock(&(rules->forks[ph->r_fork]));
	ph_print(B, ph, FORK, false);
	pthread_mutex_lock(&(rules->m_check_meal));
	ph_print(G, ph, EAT, false);
	ph->time_last_meal = crono();
	pthread_mutex_unlock(&(rules->m_check_meal));
	ft_usleep(ph->rules->time_to_eat, ph->rules);
	(ph->num_meals)++;
	pthread_mutex_unlock(&(rules->forks[ph->l_fork]));
	pthread_mutex_unlock(&(rules->forks[ph->r_fork]));
}

void	*sim(void *void_ph)
{
	t_rules	*rules;
	t_philo	*philo;

	philo = (t_philo *)void_ph;
	rules = philo->rules;
	if (philo->id % 2)
		ft_usleep(philo->rules->time_to_eat, rules);
	while (rules->died == 0)
	{
		ph_life(philo);
		if (rules->all_ate)
			break;
		ph_print(Y, philo, SLEEP, false);
		ft_usleep(philo->rules->time_to_sleep, rules);
		ph_print(F, philo, THINK, false);
	}
	return (NULL);
}

void	exit_simulation(t_rules *rules, t_philo *philo)
{
	int	i;

	i = 0;
	if (rules->philo_units == 1)
	{
		return ;
	}
	while (i < rules->philo_units)
	{
		pthread_join(philo[i].threat_id, NULL);
		i++;
	}
	i = 0;
	while (i < rules->philo_units)
	{
		pthread_mutex_destroy(&(rules->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(rules->m_printer));
	pthread_mutex_destroy(&(rules->m_check_meal));
	pthread_mutex_destroy(&(rules->m_dead));
}

int	init_simulation(t_rules *rules)
{
	t_philo	*ph;
	int		i;

	i = 0;
	ph = rules->philos;
	rules->start_time = crono();
	while (i < rules->philo_units)
	{
		if (pthread_create(&(ph[i].threat_id), NULL, sim, &(rules->philos[i])))
			return (THREADS);
		ph[i].time_last_meal = crono();
		i++;
	}
	check_death(rules, rules->philos);
	exit_simulation(rules, ph);
	return (0);
}
