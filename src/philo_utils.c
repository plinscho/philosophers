/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 20:13:05 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/12 18:51:23 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_print(char *color, t_philo *philo, char *s, bool dead)
{
	pthread_mutex_lock(&philo->rules->m_printer);
	if (dead == false)
	{
		printf("%s%llu ", color, crono() - philo->rules->start_time);
		printf("Philo[%d] %s\n%s", philo->id, s, E);
	}
	else
	{
		printf("%s%llu ", color, crono() - philo->rules->start_time);
		printf("Philo[%d] %s\n%s", philo->id, s, E);
	}
	pthread_mutex_unlock(&philo->rules->m_printer);
	return ;
}

void	ft_usleep(uint64_t ms_wait)
{
	ms_wait += crono();
	while (crono() <= ms_wait)
		usleep(100);
}

// funtion return 0 for succes or -1 for failure
uint64_t	crono(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) < 0)
		write(2, "gettimeofday() function failed\n", 32);
	return(t.tv_sec * 1000 + t.tv_usec / 1000);
}

/*
void		print_philo(t_rules *data)
{
	t_philo	tmp;
	int		i;

	i = 0;
	while (i < data->philo_units)
	{
		tmp = data->philos[i];
		printf("\n_____________________\n");
		printf("Philo id: 	[%d]\n", tmp.id);
		printf("Philo nºmeals:	[%d]\n", tmp.num_meals);
		printf("Philo nºmeals:	[%lld]\n", tmp.time_last_meal);
		printf("_____________________\n");
		i++;
	}
};
*/