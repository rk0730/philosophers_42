/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_message.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 19:10:51 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/15 19:57:53 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// startからの経過時間（ミリ秒）を返す
unsigned int	ft_get_time(t_common_data *data)
{
	struct timeval	now;
	unsigned int	result;

	gettimeofday(&now, NULL);
	pthread_mutex_lock(&data->lock_info);
	result = (now.tv_sec - data->start_time.tv_sec) * 1000 + (now.tv_usec
			- data->start_time.tv_usec) / 1000;
	pthread_mutex_unlock(&data->lock_info);
	return (result);
}

// 誰かが死んでいる、あるいは全員規定回数食べ切っているかどうか確認する
int	ft_is_finished(t_common_data *data)
{
	int	result;
	int	i;

	result = 0;
	pthread_mutex_lock(&data->lock_info);
	if (data->dead > 0)
		result = 1;
	if (data->num_philo_must_eat != -1)
	{
		i = 0;
		while (i < data->num_of_philo)
		{
			if (data->eat_count[i] < data->num_philo_must_eat)
				break ;
			i++;
		}
		if (i == data->num_of_philo)
			result = 1;
	}
	pthread_mutex_unlock(&data->lock_info);
	return (result);
}

void	ft_message(t_philo *philo, t_message_type type)
{
	unsigned int	time;

	time = ft_get_time(philo->data);
	if (ft_is_finished(philo->data) == 0)
	{
		if (type == FIRST_FORK || type == SECOND_FORK)
			printf("%u %d has taken a fork\n", time, philo->id);
		if (type == SECOND_FORK)
			printf("%u %d is eating\n", time, philo->id);
		if (type == SLEEP)
			printf("%u %d is sleeping\n", time, philo->id);
		if (type == THINK)
			printf("%u %d is thinking\n", time, philo->id);
		if (type == DIE)
			printf("%u %d died\n", time, philo->id);
	}
}
