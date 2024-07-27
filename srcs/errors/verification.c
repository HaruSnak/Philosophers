/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:14:25 by shmoreno          #+#    #+#             */
/*   Updated: 2024/04/10 15:45:50 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// Check if the arguments are correct and convert them to integers
void	ft_verif_number(t_philo *philo, char **argv)
{
	philo->nb_of_philo = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]);
	philo->time_to_eat = ft_atoi(argv[3]);
	philo->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		philo->nb_times_philo_eat = ft_atoi(argv[5]);
	else
		philo->nb_times_philo_eat = -1;
	if (philo->nb_of_philo < 1 || philo->nb_of_philo > 200
		|| philo->time_to_die < 1 || philo->time_to_eat < 1
		|| philo->time_to_sleep < 1)
		ft_error("Your arguments are not correct\n");
}

// Check if the arguments are correct
void	ft_verif_base(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	if (argc < 5 || argc > 6)
		ft_error("You need to put 4 or 5 arguments!\n");
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!(argv[i][j] >= '0' && argv[i][j] <= '9'))
				ft_error("Your arguments are not correct!\n");
			j++;
		}
		i++;
	}
}
