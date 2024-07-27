/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 14:49:25 by shmoreno          #+#    #+#             */
/*   Updated: 2024/04/10 15:39:12 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philo.h"

// Convert a string to an integer
int	ft_atoi(const char *str)
{
	size_t	number;
	size_t	negativ_number;
	size_t	i;

	negativ_number = 1;
	i = 0;
	number = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		negativ_number *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		number *= 10;
		number += str[i] - '0';
		i++;
	}
	return (number * negativ_number);
}

// Get the time in milliseconds
size_t	ft_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
	{
		printf("Error: gettimeofday()\n");
	}
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

// Print the message
void	ft_print(t_philo *philo, int id, char *str)
{
	pthread_mutex_lock(philo->m_write);
	if (!ft_verify_loop(philo))
		printf("%ld %d %s\n", (ft_time() - philo->s_time),
			id, str);
	pthread_mutex_unlock(philo->m_write);
}

// Sleep for a certain amount of time
int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = ft_time();
	while ((ft_time() - start) < milliseconds)
		usleep(500);
	return (0);
}
