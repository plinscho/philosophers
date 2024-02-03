/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 12:41:01 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/03 18:31:00 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"


int	ph_atoi(char *str)
{
	long	l_ret;
	int		i_ret;
	int		count;
	
	count = 0;
	l_ret = 0;
	i_ret = 0;
	while (str[count])
	{
		l_ret *= 10;
		l_ret += (str[count] - '0');
		count++;
	}
	if (l_ret > INT_MAX)
		exit_philo(str, "Number is bigger than INT_MAX.", BAD_INPUT);
	i_ret = (int)l_ret;
	return (i_ret);
}

int	input_str_check(char **argv)
{
	int i;
	int	j;

	i = 1;
	while (argv[i] != NULL)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9') || j > 9)
				return (exit_philo(argv[i], "Input is invalid.", BAD_INPUT));
			j++;
		}
		i++;
	}
	return (0);	
}

int	input_check(int argc, char **argv)
{
	if (!(argc == 5 || argc == 6))
		return (exit_philo("ARGC", "Not enough arguments\n\
	[nº_philos][time_die][time_eat][time_sleep]( [nº_meals] )", BAD_INPUT));
	if (input_str_check(argv))
		return (1);
	return (0);
}