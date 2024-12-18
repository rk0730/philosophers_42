/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_message.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 12:02:53 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/18 17:08:04 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_get_args(t_common_data *data, t_data_type type)
{
	int	result;

	pthread_mutex_lock(&data->lock_args);
	if (type == NUM_OF_PHILO)
		result = data->args->num_of_philo;
	else if (type == TIME_TO_DIE)
		result = data->args->time_to_die;
	else if (type == TIME_TO_EAT)
		result = data->args->time_to_eat;
	else if (type == TIME_TO_SLEEP)
		result = data->args->time_to_sleep;
	else if (type == NUM_PHILO_MUST_EAT)
		result = data->args->num_philo_must_eat;
	else
	{
		result = -1;
		printf("error in ft_get_args");
	}
	pthread_mutex_unlock(&data->lock_args);
	return (result);
}

// startからの経過時間（ミリ秒）を返す
unsigned int	ft_get_time(t_common_data *data)
{
	struct timeval	now;
	unsigned int	result;

	gettimeofday(&now, NULL);
	pthread_mutex_lock(&data->lock_data);
	result = (now.tv_sec - data->start_time.tv_sec) * 1000 + (now.tv_usec
			- data->start_time.tv_usec) / 1000;
	pthread_mutex_unlock(&data->lock_data);
	return (result);
}

// 誰かが死んでいる、あるいは全員規定回数食べ切っているかどうか確認する
int	ft_is_finished(t_common_data *data)
{
	int	result;
	int	i;

	result = 0;
	pthread_mutex_lock(&data->lock_data);
	if (data->dead > 0)
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
