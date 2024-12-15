/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:32:12 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/15 16:15:15 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_common_data	*data;

	data = (t_common_data *)malloc(sizeof(t_common_data));
	RKITAO("debug mode\n");
	if (ft_arg(argc, argv, data) == 1)
		return (1);
	printf("param\n");
	printf("num_of_philo: %d\n", data->num_of_philo);
	printf("time_to_die: %d\n", data->time_to_die);
	printf("time_to_eat: %d\n", data->time_to_eat);
	printf("time_to_sleep: %d\n", data->time_to_sleep);
	printf("num_philo_must_eat: %d\n", data->num_philo_must_eat);
	return (0);
}
