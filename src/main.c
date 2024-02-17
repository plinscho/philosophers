/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:30:32 by plinscho          #+#    #+#             */
/*   Updated: 2024/02/17 17:08:21 by plinscho         ###   ########.fr       */
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

int main(int argc, char **argv)
{
	t_rules	rules;
	int		i;

	if (input_check(argc, argv))	// make solution for 1 philosopher.
		return (1);
	if (init_struct_mutex(argc, argv, &rules))
		return (2);
	if (init_simulation(&rules))
		return (3);
	pthread_mutex_unlock(&(rules.m_dead));
	check_philos(&rules);
	i = 0;
	while (i < rules.philo_units)
	{
		pthread_join(rules.philos[i].threat_id, NULL);
		i++;
	}
	return (0);
}


