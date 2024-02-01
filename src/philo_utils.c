/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 20:13:05 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/01 18:43:26 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			ph_usleep(uint64_t ms_wait)
{
	while (ms_wait > 0)
	{
		ms_wait--;
	}
	return (0);
}

uint64_t	time_inc(uint64_t past, uint64_t present)
{
	return (present - past);
}

// funtion return 0 for succes or -1 for failure
uint64_t	crono(void)
{
	struct timeval	t;

	if (gettimeofday(&t, NULL) < 0)
		return (0);
	return(t.tv_sec * 1000 + t.tv_usec / 1000);
}

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
		printf("Philo r_fork:	[%d]\n", tmp.r_fork_id);
		printf("Philo l_fork:	[%d]\n", tmp.l_fork_id);
		printf("Philo nºmeals:	[%d]\n", tmp.num_meals);
		printf("Philo nºmeals:	[%lld]\n", tmp.time_last_meal);
		printf("_____________________\n");
		i++;
	}
};