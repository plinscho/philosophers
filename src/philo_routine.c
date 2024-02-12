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

void	ph_life(t_philo *ph)
{
	t_rules	*rules;

	rules = ph->rules;
	pthread_mutex_lock(&(rules->forks[ph->l_fork]));
	ph_print(R, ph, FORK, false);
	pthread_mutex_lock(&(rules->forks[ph->r_fork]));
	ph_print(B, ph, FORK, false);
	pthread_mutex_lock(&(rules->m_check_meal));
	ph_print(G, ph, EAT, false);
	ph->time_last_meal = crono();
	pthread_mutex_unlock(&(rules->m_check_meal));
	ft_usleep(ph->rules->time_to_eat);
	pthread_mutex_unlock(ph->r_fork);
	pthread_mutex_unlock(ph->l_fork);
	ph_print(Y, ph, SLEEP, false);
	ft_usleep(ph->rules->time_to_sleep);
	ph_print(F, ph, THINK, false);
}

void	*sim(void *void_ph)
{
	t_rules	*rules;
	t_philo	*philo;
	int		i;

	philo = (t_philo *)void_ph;
	rules = philo->rules;
	i = 0;
	if (philo->id % 2)
		ft_usleep(philo->rules->time_to_eat);
	while (rules->died != 0)
	{
		ph_life(philo);
		if (rules->all_ate)
			break;

	}
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
	check_death(void, NULL);
	return (0);
}
