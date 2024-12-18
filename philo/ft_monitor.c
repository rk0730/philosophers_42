/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_monitor.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:29:34 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/18 18:20:26 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_is_dead(t_common_data *data)
{
	int	num_of_philo;
	int	i;

	num_of_philo = ft_get_args(data, NUM_OF_PHILO);
	i = 0;
	while (i < num_of_philo)
	{
		if (data->philos[i].last_meal_time
			- ft_get_time(data) > ft_get_args(data, TIME_TO_DIE))
			return (1);
		i++;
	}
	return (0);
}

// 誰かが死んでいる、あるいは全員規定回数食べ切っているかどうか確認する
int	ft_is_finished(t_common_data *data)
{
	int	result;
	int	i;

	result = 0;
	pthread_mutex_lock(&data->lock_data);
	if (ft_is_dead(data) > 0)
		result = 1;
	if (ft_get_args(data, NUM_PHILO_MUST_EAT) != -1)
	{
		i = 0;
		while (i < data->args->num_of_philo)
		{
			if (data->eat_count[i] < data->args->num_philo_must_eat)
				break ;
			i++;
		}
		if (i == data->args->num_of_philo)
			result = 1;
	}
	pthread_mutex_unlock(&data->lock_data);
	return (result);
}
