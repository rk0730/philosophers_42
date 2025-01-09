/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 15:09:20 by kitaoryoma        #+#    #+#             */
/*   Updated: 2025/01/09 15:09:21 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// 誰かが死んでいるなら、その人のidを返す
int	ft_is_dead(t_common_data *data)
{
	int	num_of_philo;
	int	i;
	int	time;

	num_of_philo = ft_get_args(data, NUM_OF_PHILO);
	i = 0;
	time = ft_get_time(data);
	pthread_mutex_lock(&data->lock_data);
	while (i < num_of_philo)
	{
		if (time - data->last_meal_time[i] > ft_get_args(data, TIME_TO_DIE))
			break ;
		i++;
	}
	pthread_mutex_unlock(&data->lock_data);
	if (i == num_of_philo)
		return (0);
	else
		return (i + 1);
}

// 誰かが死んでいる、あるいは全員規定回数食べ切っているかどうか確認する
int	ft_is_finished(t_common_data *data)
{
	int	result;
	int	i;

	result = 0;
	if (ft_is_dead(data) > 0)
		result = 1;
	if (ft_get_args(data, NUM_PHILO_MUST_EAT) != -1)
	{
		i = 0;
		pthread_mutex_lock(&data->lock_data);
		while (i < ft_get_args(data, NUM_OF_PHILO))
		{
			if (data->eat_count[i] < data->args->num_philo_must_eat)
				break ;
			i++;
		}
		pthread_mutex_unlock(&data->lock_data);
		if (i == ft_get_args(data, NUM_OF_PHILO))
			result = 1;
	}
	return (result);
}
