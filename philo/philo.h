/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:22:48 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/15 19:00:35 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

# ifdef RKITAO_DEBUG
#  define RKITAO(fmt, ...) printf(fmt, ##__VA_ARGS__)
# else
#  define RKITAO(fmt, ...)
# endif

// 全員が共通で使うデータ
typedef struct s_common_data
{
	//引数からもらう情報
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_philo_must_eat;
	struct timeval	start_time;
	pthread_mutex_t	lock_info;
	pthread_mutex_t	*forks;
	int				dead;
	pthread_mutex_t	lock_dead;
	int				*eat_count;
	pthread_mutex_t	lock_eat_count;
	struct s_philo *philos;
	pthread_t *threads;
	
}					t_common_data;

// 各々が使うデータ　threadの引数になる
typedef struct s_philo
{
	t_common_data	*data;
	// 1からnum_of_philo
	int				id;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	int				*my_eat_count;
	struct timeval last_meal_time;
}					t_philo;

// utils
int					ft_isdigit(int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_is_all_digit(char *str);
// src
int					ft_arg(int argc, char **argv, t_common_data *param);
void	*ft_routine(void *arg);

#endif