/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:22:48 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/15 13:27:18 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

# ifdef RKITAO_DEBUG
#  define RKITAO(fmt, ...) printf(fmt, ##__VA_ARGS__)
# else
#  define RKITAO(fmt, ...)
# endif

typedef struct s_param
{
	//引数からもらう情報
	int	num_of_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	num_philo_must_eat;
}		t_param;

// utils
int	ft_isdigit(int c);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
int	ft_atoi(const char *str);
// src
int	ft_arg(int argc, char **argv, t_param *param);

#endif