/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:01:41 by shmoreno          #+#    #+#             */
/*   Updated: 2024/04/10 15:57:07 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

// Initialize the philo struct
void	ft_init_philo(t_philo *philos, pthread_mutex_t *forks,
	t_mutex *mutex, char **argv)
{
	int	i;

	i = 0;
	while (i != ft_atoi(argv[1]))
	{
		philos[i].philo = i + 1;
		philos[i].eat = 0;
		philos[i].nb_meal = 0;
		ft_verif_number(&philos[i], argv);
		philos[i].s_time = ft_time();
		philos[i].last_meal = ft_time();
		philos[i].m_write = &mutex->write;
		philos[i].m_dead = &mutex->dead;
		philos[i].m_meal = &mutex->current_meal;
		philos[i].dead = &mutex->f_dead;
		philos[i].l_fork = &forks[i];
		if (i == 0)
			philos[i].r_fork = &forks[philos[i].nb_of_philo - 1];
		else
			philos[i].r_fork = &forks[i - 1];
		i++;
	}
}

// Create the threads and join them to the main thread
int	ft_thread(t_mutex *mutex, pthread_mutex_t *forks)
{
	pthread_t	monitor;
	int			i;

	i = 0;
	if (pthread_create(&monitor, NULL, &ft_monitor, mutex->philos) != 0)
		ft_destroy_mutex(mutex, forks);
	while (i < mutex->philos[0].nb_of_philo)
	{
		if (pthread_create(&mutex->philos[i].thread, NULL, &ft_routine,
				&mutex->philos[i]) != 0)
			ft_destroy_mutex(mutex, forks);
		i++;
	}
	if (pthread_join(monitor, NULL) != 0)
		ft_destroy_mutex(mutex, forks);
	i = 0;
	while (i < mutex->philos[0].nb_of_philo)
	{
		if (pthread_join(mutex->philos[i].thread, NULL) != 0)
			ft_destroy_mutex(mutex, forks);
		i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_mutex			mutex;
	t_philo			philos[MAX_PHILO];
	pthread_mutex_t	forks[MAX_PHILO];
	int				i;

	i = 0;
	ft_verif_base(argc, argv);
	mutex.philos = philos;
	mutex.f_dead = 0;
	pthread_mutex_init(&mutex.dead, NULL);
	pthread_mutex_init(&mutex.write, NULL);
	pthread_mutex_init(&mutex.current_meal, NULL);
	while (i < ft_atoi(argv[1]))
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	ft_init_philo(philos, forks, &mutex, argv);
	ft_thread(&mutex, forks);
	ft_destroy_mutex(&mutex, forks);
	return (0);
}
