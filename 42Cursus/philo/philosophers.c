/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:03:26 by auferran          #+#    #+#             */
/*   Updated: 2023/07/09 18:08:30 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_philo *philo, t_mutex *mutex, int index)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&mutex->timer);
	pthread_mutex_destroy(&mutex->philo_eated);
	pthread_mutex_destroy(&mutex->is_dead);
	while (i < index)
	{
		pthread_mutex_destroy(&philo[i].fork);
		i++;
	}
}

void	waiting_close_thread(t_philo *philo, int index)
{
	int	i;

	i = 0;
	if (index == -1)
	{
		while (i < philo->value->nb_philo)
		{
			pthread_join(philo[i].thread_id, NULL);
			i++;
		}
	}
	else
	{
		while (i < index)
		{
			pthread_join(philo[i].thread_id, NULL);
			i++;
		}
	}
}

void	infinit_while(t_philo *philo, t_value value, t_mutex *mutex)
{
	while (4)
	{
		pthread_mutex_lock(&mutex->philo_eated);
		if (*value.philo_eated == value.nb_philo)
		{
			pthread_mutex_unlock(&mutex->philo_eated);
			break ;
		}
		pthread_mutex_unlock(&mutex->philo_eated);
		if (checker_death(philo))
			break ;
		usleep(200);
	}
	pthread_mutex_lock(&mutex->is_dead);
	(*value.is_dead)++;
	pthread_mutex_unlock(&mutex->is_dead);
}

int	create_thread(t_philo *philo, t_value *value, t_mutex *mutex)
{
	int	i;

	i = 0;
	while (i < philo->value->nb_philo)
	{
		philo[i].value = value;
		philo[i].mutex = mutex;
		if (pthread_create(&philo[i].thread_id, NULL, start_thread, &philo[i]))
		{
			pthread_mutex_lock(&mutex->is_dead);
			(*value->is_dead)++;
			pthread_mutex_unlock(&mutex->is_dead);
			return (error(4), i);
		}
		i++;
	}
	return (-1);
}

void	philosophers(t_philo *philo, t_value value)
{
	int				index;
	t_mutex			mutex;
	struct timeval	start;

	index = 0;
	if (!init_mutex(philo, &mutex))
		return (error(3));
	gettimeofday(&start, NULL);
	value.timer_start = (start.tv_sec * 1000) + \
		(start.tv_usec / 1000);
	index = create_thread(philo, &value, &mutex);
	if (index == -1)
		infinit_while(philo, value, &mutex);
	waiting_close_thread(philo, index);
	destroy_mutex(philo, &mutex, index);
}
