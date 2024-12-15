/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:32:12 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/15 18:30:45 by kitaoryoma       ###   ########.fr       */
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
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->num_of_philo);
	data->threads = (pthread_t *)malloc(sizeof(pthread_t) * data->num_of_philo);
	pthread_mutex_init(&data->lock_arg, NULL);
	pthread_mutex_init(&data->lock_dead, NULL);
	pthread_mutex_init(&data->lock_eat_count, NULL);
}

void	ft_gen_threads(t_common_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->lock_arg);
	while (i < data->num_of_philo)
	{
		// t_philoの初期化
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		if (i == 0)
			data->philos[i].l_fork = &data->forks[data->num_of_philo - 1];
		else
			data->philos[i].l_fork = &data->forks[i - 1];
		data->philos[i].r_fork = &data->forks[i];
		data->philos[i].my_eat_count = &data->eat_count[i];
		pthread_create(&(data->threads[i]), NULL, ft_routine,
			&(data->philos[i]));
		i++;
	}
	pthread_mutex_unlock(&data->lock_arg);
}

int	main(int argc, char **argv)
{
	t_common_data	*data;
	int				i;

	data = (t_common_data *)malloc(sizeof(t_common_data));
	RKITAO("debug mode\n");
	if (ft_arg(argc, argv, data) == 1)
		exit(EXIT_FAILURE);
	ft_init_common_data(data);
	// スレッドを作成する
	ft_gen_threads(data);
	// スレッドの終了を待つ
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join(data->threads[i], NULL);
		i++;
	}
	return (0);
}
