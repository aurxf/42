/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: auferran <auferran@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/01 05:02:04 by auferran          #+#    #+#             */
/*   Updated: 2023/07/09 18:18:20 by auferran         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	meal_eated(t_philo *philo_thread)
{
	philo_thread->meal_eated++;
	pthread_mutex_lock(&philo_thread->mutex->philo_eated);
	if (philo_thread->meal_eated == philo_thread->value->nb_meal)
		(*philo_thread->value->philo_eated)++;
	pthread_mutex_unlock(&philo_thread->mutex->philo_eated);
	usleep(200);
}

void	eating(t_philo *philo_thread)
{
	if (philo_thread->index % 2 == 0)
	{
		if (!lock_modulo_2(philo_thread))
			return ;
		timer_last_meal(philo_thread);
		print(philo_thread, "is eating\n");
		usleep(philo_thread->value->time_eat * 1000);
		unlock_modulo_2(philo_thread);
	}
	else
	{
		if (!lock(philo_thread))
			return ;
		timer_last_meal(philo_thread);
		print(philo_thread, "is eating\n");
		usleep(philo_thread->value->time_eat * 1000);
		unlock(philo_thread);
	}
}

void	*start_thread(void *philo)
{
	t_philo	*philo_thread;

	philo_thread = (t_philo *)philo;
	philo_thread->meal_eated = 0;
	timer_start_philo(philo_thread);
	while (4)
	{
		if (philo_thread->index % 2)
			usleep(500);
		print(philo_thread, "is thinking\n");
		usleep(200);
		eating(philo_thread);
		if (is_dead(philo_thread))
			break ;
		meal_eated(philo_thread);
		print(philo_thread, "is sleeping\n");
		usleep(philo_thread->value->time_sleep * 1000);
	}
	return (NULL);
}

void	print(t_philo *philo_thread, char *str)
{
	struct timeval	inwhile;

	pthread_mutex_lock(&philo_thread->mutex->is_dead);
	if (*philo_thread->value->is_dead == 0)
	{
		gettimeofday(&inwhile, NULL);
		printf("%ld %d %s", ((inwhile.tv_sec * 1000) + \
			(inwhile.tv_usec / 1000) - \
			philo_thread->value->timer_start), philo_thread->index, str);
	}
	else if (*philo_thread->value->is_dead > 0 && !ft_strcmp(str, "died\n"))
	{
		gettimeofday(&inwhile, NULL);
		printf("%ld %d %s", ((inwhile.tv_sec * 1000) + \
			(inwhile.tv_usec / 1000) - \
			philo_thread->value->timer_start), philo_thread->index, str);
	}
	pthread_mutex_unlock(&philo_thread->mutex->is_dead);
}

int	init_mutex(t_philo *philo, t_mutex *mutex)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&mutex->timer, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&mutex->philo_eated, NULL) != 0)
		return (0);
	if (pthread_mutex_init(&mutex->is_dead, NULL) != 0)
		return (0);
	while (i < philo->value->nb_philo)
	{
		if (pthread_mutex_init(&philo[i].fork, NULL) != 0)
			return (0);
		i++;
	}
	return (1);
}
