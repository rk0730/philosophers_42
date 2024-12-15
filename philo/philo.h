/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:22:48 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/15 16:13:21 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifdef RKITAO_DEBUG
#  define RKITAO(fmt, ...) printf(fmt, ##__VA_ARGS__)
# else
#  define RKITAO(fmt, ...)
# endif

typedef struct s_common_data
{
	//引数からもらう情報
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_philo_must_eat;
	pthread_mutex_t	*forks;
	int				dead;
	int				*eat_count;

}					t_common_data;

// utils
int					ft_isdigit(int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_is_all_digit(char *str);
// src
int					ft_arg(int argc, char **argv, t_common_data *param);

#endif