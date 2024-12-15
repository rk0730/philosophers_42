/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:32:12 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/15 16:30:26 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_common_data(t_common_data *data)
{
	int	i;

	//　dataの初期化
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->num_of_philo);
	data->eat_count = (int *)malloc(sizeof(int) * data->num_of_philo);
	i = 0;
	while (i < data->num_of_philo)
	{
		data->eat_count[i] = 0;
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	data->dead = 0;
	pthread_mutex_init(&data->lock_arg, NULL);
	pthread_mutex_init(&data->lock_dead, NULL);
	pthread_mutex_init(&data->lock_eat_count, NULL);
}

int	main(int argc, char **argv)
{
	t_common_data	*data;

	data = (t_common_data *)malloc(sizeof(t_common_data));
	RKITAO("debug mode\n");
	if (ft_arg(argc, argv, data) == 1)
		exit(EXIT_FAILURE);
	ft_init_common_data(data);
	return (0);
}
