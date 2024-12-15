/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:09:48 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/15 16:12:14 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_arg(int argc, char **argv, t_common_data *data)
{
	int	i;

	// 引数の数が正しいか確認
	if (argc < 5 || argc > 6)
	{
		write(STDERR_FILENO,
			"Usage: ./philo number_of_philosophers time_to_die time_to_eat "
			"time_to_sleep [number_of_times_each_philosopher_must_eat]\n",
			120);
		return (1);
	}
	// 引数がすべて数字かどうかチェック
	i = 1;
	while (i < argc)
	{
		if (ft_is_all_digit(argv[i]))
			i++;
		else
			break ;
	}
	if (i != argc)
	{
		write(STDERR_FILENO,
			"Invalid argument. All arguments should be digits.\n", 50);
		return (1);
	}
	// 引数を数値に変換
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->num_philo_must_eat = ft_atoi(argv[5]);
	else
		data->num_philo_must_eat = -1;
	// 引数が不正な場合の処理
	if (data->num_of_philo <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0 || (argc == 6
			&& data->num_philo_must_eat <= 0))
	{
		write(STDERR_FILENO, "Invalid argument\n", 17);
		return (1);
	}
	return (0);
}
