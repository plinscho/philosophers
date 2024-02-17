/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 13:10:39 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/17 15:41:21 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	exit_philo(char *input, char *err_msg, error_code err_code)
{
	printf("[%s]: %s\n\n", input, err_msg);
	return(err_code);
}

int	free_struct(t_rules *data)
{
	pthread_mutex_destroy(&(data->m_printer));
	pthread_mutex_destroy(&(data->m_dead));
	pthread_mutex_destroy(&(data->m_start));
	return (0);
}
