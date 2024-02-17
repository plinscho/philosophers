/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 20:13:05 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/17 18:08:33 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_print(char *color, t_philo *philo, char *s, bool dead)
{
	uint64_t	i;
	bool		finish;

	pthread_mutex_lock(&philo->rules->m_printer);
	pthread_mutex_lock(&philo->rules->m_dead);
	finish = philo->rules->died;
	pthread_mutex_unlock(&philo->rules->m_dead);
	i = crono() - philo->rules->start_time;
	if (!finish || dead == true)
		printf("%s%llu Philo[%d] %s\n%s", color, i, philo->id, s, E);
	pthread_mutex_unlock(&philo->rules->m_printer);
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
	return (t.tv_sec * 1000 + (t.tv_usec / 1000));
}
