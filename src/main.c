/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plinscho <plinscho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 18:30:32 by plinscho          #+#    #+#             */
/*   Updated: 2024/01/31 20:42:12 by plinscho         ###   ########.fr       */
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

//	argc:		0			1					2			3				4		
// input is [./philo] [number of philos] [time to die] [time_to_eat] [time_to_sleep] [(5)]
int	init_struct_mutex(int argc, char **argv, t_rules *rules)
{
	rules->philo_units = (uint64_t)ph_atoi(argv[1]);
	rules->time_to_die = (uint64_t)ph_atoi(argv[2]);
	rules->time_to_eat = (uint64_t)ph_atoi(argv[3]);
	rules->time_to_sleep = (uint64_t)ph_atoi(argv[4]);
	rules->meals = -1;	// value if no additional option
	rules->died = 0;
	rules->all_ate = 0;
	if (argc > 5)
		rules->meals = (uint64_t)ph_atoi(argv[5]);
	if (rules->philo_units == 0)
		return (exit_philo(NULL, "At least 1 philo has to exist...\n", BAD_INPUT));
	if (init_mutex(rules))
		return (exit_philo("THREADS", "Thread creation returned 1.\n", MUTEX));
	init_philo(rules);
	return (0);	
}

int main(int argc, char **argv)
{
	t_rules		rules;

	if (input_check(argc, argv))
		return (1);
	if (init_struct_mutex(argc, argv, &rules))
		return (free_struct(&rules));
//	print_philo(&rules);
	if (start_simulation(&rules))
		return(free_struct(&rules));
//	start_simulation(&rules);
//	free_struct(&rules);
	return (0);
}


