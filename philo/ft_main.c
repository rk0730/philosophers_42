/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:32:12 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/15 13:16:17 by rkitao           ###   ########.fr       */
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
	ft_arg(argc, argv, param);
	return (0);
}