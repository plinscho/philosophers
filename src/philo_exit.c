/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 13:10:39 by plinscho          #+#    #+#             */
/*   Updated: 2024/01/31 19:57:59 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_philo(char *input, char *err_msg, error_code err_code)
{
	printf("[%s]: %s\n\n", input, err_msg);
	return(err_code);
}

int	free_struct(t_rules *table)
{
	int i = -1;
	while (++i < table->philo_units)
		pthread_mutex_destroy(&(table->forks[i]));
	pthread_mutex_destroy(&(table->printer));
	pthread_mutex_destroy(&(table->check_meal));
	return (exit_philo("THREADS", "Error creating threads.\n", THREADS));
}