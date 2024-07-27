/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:13:43 by shmoreno          #+#    #+#             */
/*   Updated: 2024/04/10 15:44:10 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// Print the error message and exit the program
void	ft_error(char *str)
{
	printf("Error: %s\n", str);
	exit(EXIT_FAILURE);
}

// Destroy the mutex
void	ft_destroy_mutex(t_mutex *mutex, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&mutex->current_meal);
	pthread_mutex_destroy(&mutex->dead);
	pthread_mutex_destroy(&mutex->write);
	while (i < mutex->philos[0].nb_of_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}
