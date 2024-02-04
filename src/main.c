/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:30:32 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/04 14:30:13 by plinscho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

◦ (1)	number_of_philosophers: es el nº de filósofos, pero también el nº de tenedores.

◦ (2)	time_to_die (en milisegundos): si un filósofo no empieza a comer en time_to_die 
milisegundos desde el comienzo de su ultima comida o desde el principio de la
simulación, este morirá.

◦ (3)	time_to_eat (en milisegundos): es el tiempo que tiene un filósofo para comer.
Durante ese tiempo, tendrá los tenedores ocupados.
>time_to_sleep (en milisegundos): es el tiempo que tiene un filósofo para
dormir.

◦ (4) 	time_to_sleep (en milisegundos): es el tiempo que tiene un filósofo para
dormir.

◦ (5)	number_of_times_each_philosopher_must_eat: (argumento opcional): si to-
dos los filósofos comen al menos number_of_times_each_philosopher_must_eat
veces, la simulación se detendrá. Si no se especifica, la simulación se detendrá
con la muerte de un filósofo.


• Cada filósofo tendrá asignado un nº del 1 al number_of_philosophers.
• El filósofo nº 1 se sentará al lado del filósofo nº number_of_philosophers.
Cualquier otro filósofo nº N se sentarán entre el filósofo nº N - 1 y el filósofo
nº N + 1

*/

#include "philo.h"

// 	joining threads created before.
int	join_threads(t_rules *data)
{
	int			i;
	pthread_t	p;

	i = 0;
	while (i < data->philo_units && data->died == 0)
	{
		p = data->philos[i].threat_id;
		if (pthread_join(p, NULL) != 0)
			return (exit_philo("JOIN_THREADS", "Error joining threads.", THREADS));
		i++;
	}
	return (0);
}

int main(int argc, char **argv)
{
	t_rules		rules;

	if (input_check(argc, argv))	// make solution for 1 philosopher.
		return (1);
	if (init_struct_mutex(argc, argv, &rules))
		return (2);
	if (init_simulation(&rules))
		return(free_struct(&rules));
	check_philos(&rules);
	if (join_threads(&rules))
		return (free_struct(&rules));
	free_struct(&rules);
	return (0);
}


