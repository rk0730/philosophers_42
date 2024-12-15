/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:32:12 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/15 13:48:29 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_param	*param;

	param = (t_param *)malloc(sizeof(t_param));
	(void)argv;
	RKITAO("debug mode\n");
	printf("start %d\n", argc);
	if (ft_arg(argc, argv, param) == 1)
		return (1);
	printf("param\n");
	printf("num_of_philo: %d\n", param->num_of_philo);
	printf("time_to_die: %d\n", param->time_to_die);
	printf("time_to_eat: %d\n", param->time_to_eat);
	printf("time_to_sleep: %d\n", param->time_to_sleep);
	printf("num_philo_must_eat: %d\n", param->num_philo_must_eat);
	return (0);
}
