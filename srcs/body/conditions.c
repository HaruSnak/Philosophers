/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 22:08:44 by shmoreno          #+#    #+#             */
/*   Updated: 2024/04/10 15:53:57 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// Check if the number of meals is reached by all the philosophers
int	ft_v_current_meal(t_philo *philos)
{
	int	i;
	int	meal_eat;

	i = 0;
	meal_eat = 0;
	if (philos[0].nb_times_philo_eat == -1)
		return (0);
	while (i < philos[0].nb_of_philo)
	{
		pthread_mutex_lock(philos[i].m_meal);
		if (philos[i].nb_meal >= philos[i].nb_times_philo_eat)
			meal_eat++;
		pthread_mutex_unlock(philos[i].m_meal);
		i++;
	}
	if (meal_eat == philos[0].nb_of_philo)
	{
		pthread_mutex_lock(philos[0].m_dead);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].m_dead);
		return (1);
	}
	return (0);
}

// Check if the philosopher is dead by comparing the time of his last meal
int	ft_is_dead(t_philo *philo, size_t time_to_die)
{
	pthread_mutex_lock(philo->m_meal);
	if (ft_time() - philo->last_meal >= time_to_die && philo->eat == 0)
		return (pthread_mutex_unlock(philo->m_meal), 1);
	return (pthread_mutex_unlock(philo->m_meal), 0);
}

// Check if the philosopher is dead and print the message
int	ft_check_if_dead(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos[0].nb_of_philo)
	{
		if (ft_is_dead(&philos[i], philos[i].time_to_die))
		{
			ft_print(&philos[i], philos[i].philo, "died");
			pthread_mutex_lock(philos[0].m_dead);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].m_dead);
			return (1);
		}
		i++;
	}
	return (0);
}

// Monitor the philosophers
void	*ft_monitor(void *ptr)
{
	t_philo	*philos;

	philos = (t_philo *)ptr;
	while (1)
	{
		if (ft_check_if_dead(philos) == 1
			|| ft_v_current_meal(philos) == 1)
			break ;
	}
	return (ptr);
}

// Verify if the program is still running or if it has stopped
int	ft_verify_loop(t_philo *philo)
{
	pthread_mutex_lock(philo->m_dead);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->m_dead), 1);
	return (pthread_mutex_unlock(philo->m_dead), 0);
}
