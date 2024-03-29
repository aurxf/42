/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/07 16:51:41 by auferran          #+#    #+#             */
/*   Updated: 2023/07/09 16:32:46 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_timer_2(t_philo *philo)
{
	long int		time;
	struct timeval	inwhile_death;

	gettimeofday(&inwhile_death, NULL);
	time = (inwhile_death.tv_sec * 1000) + \
		(inwhile_death.tv_usec / 1000);
	if ((time - philo->last_m) > philo->value->time_die)
		return (1);
	return (0);
}

int	death_timer_1(t_philo *philo)
{
	long int		time;
	struct timeval	inwhile_death;

	gettimeofday(&inwhile_death, NULL);
	time = (inwhile_death.tv_sec * 1000) + \
		(inwhile_death.tv_usec / 1000);
	if (time - philo->start_p > philo->value->time_die)
		return (1);
	return (0);
}

int	is_dead(t_philo *philo_thread)
{
	pthread_mutex_lock(&philo_thread->mutex->is_dead);
	if (*philo_thread->value->is_dead > 0)
	{
		pthread_mutex_unlock(&philo_thread->mutex->is_dead);
		return (1);
	}
	pthread_mutex_unlock(&philo_thread->mutex->is_dead);
	return (0);
}

int	in_checker_death(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex->timer);
	if (philo->start_p > 0 && philo->last_m == 0)
	{
		if (death_timer_1(philo))
		{
			print(philo, "died\n");
			pthread_mutex_unlock(&philo->mutex->timer);
			return (1);
		}
	}
	if (philo->last_m > 0)
	{
		if (death_timer_2(philo))
		{
			print(philo, "died\n");
			pthread_mutex_unlock(&philo->mutex->timer);
			return (1);
		}
	}
	pthread_mutex_unlock(&philo->mutex->timer);
	return (0);
}

int	checker_death(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->value->nb_philo)
	{
		if (in_checker_death(&philo[i]))
			return (1);
		i++;
	}
	return (0);
}
