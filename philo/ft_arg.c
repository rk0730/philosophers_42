/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 13:09:48 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/15 13:22:32 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_arg(int argc, char **argv, t_param *param)
{
	(void)argv;
	(void)param;
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
	return (0);
}
