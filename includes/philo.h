/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shmoreno <shmoreno@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/01 10:01:56 by shmoreno          #+#    #+#             */
/*   Updated: 2024/04/10 16:01:08 by shmoreno         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <fcntl.h>
# include <stdarg.h>
# include <stdbool.h>
# include <stdint.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <time.h>
# include <sys/time.h>
# include <math.h>
# include <unistd.h>
# include <sys/wait.h>
# include <pthread.h>

# define MAX_PHILO 200

typedef struct s_philo
{
	int					nb_of_philo;
	size_t				time_to_die;
	size_t				time_to_eat;
	size_t				time_to_sleep;
	int					nb_times_philo_eat;
	int					philo;
	size_t				s_time;
	size_t				last_meal;
	int					eat;
	int					nb_meal;
	int					*dead;
	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	pthread_mutex_t		*m_meal;
	pthread_mutex_t		*m_dead;
	pthread_mutex_t		*m_write;
	pthread_t			thread;
}	t_philo;

typedef struct s_mutex
{
	int					f_dead;
	pthread_mutex_t		current_meal;
	pthread_mutex_t		dead;
	pthread_mutex_t		write;
	t_philo				*philos;
}	t_mutex;

//PHILOSOPHERS	philo.c

// ERRORS		verification.c
void	ft_verif_base(int argc, char **argv);
void	ft_verif_number(t_philo *philo, char **argv);
void	ft_error(char *str);
void	ft_destroy_mutex(t_mutex *mutex, pthread_mutex_t *forks);

//	TOOLS 		utils.c
int		ft_atoi(const char *str);
size_t	ft_time(void);
void	ft_print(t_philo *philo, int id, char *str);
int		ft_usleep(size_t milliseconds);

// CONDITIONS PROGRAM		condition.c
void	*ft_monitor(void *ptr);
int		ft_is_dead(t_philo *philo, size_t time_to_die);
int		ft_verify_loop(t_philo *philo);

// ROUTINE		routine.c
void	*ft_routine(void *ptr);

#endif