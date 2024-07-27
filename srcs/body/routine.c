/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 15:27:33 by shmoreno          #+#    #+#             */
/*   Updated: 2024/04/10 15:45:37 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// The philosopher takes the forks and prints the message
void	ft_forks(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	ft_print(philo, philo->philo, "has taken a fork");
	if (philo->nb_of_philo == 1)
	{
		ft_usleep(philo->time_to_die);
		pthread_mutex_unlock(philo->l_fork);
		return ;
	}
	pthread_mutex_lock(philo->r_fork);
	ft_print(philo, philo->philo, "has taken a fork");
}

// The philosopher sleeps for a certain time
void	ft_sleeping(t_philo *philo)
{
	ft_print(philo, philo->philo, "is sleeping");
	ft_usleep(philo->time_to_sleep);
}

// The philosopher thinks
void	ft_thinking(t_philo *philo)
{
	ft_print(philo, philo->philo, "is thinking");
}

// The philosopher eats and takes the forks
void	ft_eating(t_philo *philo)
{
	ft_forks(philo);
	if (philo->nb_of_philo == 1)
		return ;
	philo->eat = 1;
	ft_print(philo, philo->philo, "is eating");
	pthread_mutex_lock(philo->m_meal);
	philo->last_meal = ft_time();
	philo->nb_meal++;
	pthread_mutex_unlock(philo->m_meal);
	ft_usleep(philo->time_to_eat);
	philo->eat = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

// The routine of the philosopher
void	*ft_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->philo % 2 == 0)
		ft_usleep(1);
	while (!ft_verify_loop(philo))
	{
		ft_eating(philo);
		ft_sleeping(philo);
		ft_thinking(philo);
	}
	return (ptr);
}
