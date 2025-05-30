#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdarg.h>

# ifdef RKITAO_DEBUG
#  define RKITAO(fmt, ...) printf(fmt, ##__VA_ARGS__)
# else
#  define RKITAO(fmt, ...)
# endif

typedef struct s_args
{
	//引数からもらう情報
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_philo_must_eat;
}					t_args;

// 全員が共通で使うデータ
typedef struct s_common_data
{
	t_args			*args;
	pthread_mutex_t	lock_args;
	pthread_mutex_t	*forks;
	// そのほか全員のt_philoのデータをlockする
	pthread_mutex_t	lock_data;
	struct timeval	start_time;
	// int				dead;
	int				*eat_count;
	int				*last_meal_time;
	struct s_philo	*philos;
	pthread_t		*threads;
	pthread_mutex_t lock_printf;
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
	int				*my_last_meal_time;
}					t_philo;

typedef enum e_message_type
{
	FIRST_FORK,
	SECOND_FORK,
	SLEEP,
	THINK,
}					t_message_type;

typedef enum e_data_type
{
	NUM_OF_PHILO,
	TIME_TO_DIE,
	TIME_TO_EAT,
	TIME_TO_SLEEP,
	NUM_PHILO_MUST_EAT,

}					t_data_type;

// utils
int					ft_isdigit(int c);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_atoi(const char *str);
int					ft_is_all_digit(char *str);
// src
int					ft_arg(int argc, char **argv, t_common_data *param);
void				*ft_routine(void *arg);
int					ft_get_time(t_common_data *data);
int					ft_is_dead(t_common_data *data);
int					ft_is_finished(t_common_data *data);
int					ft_get_args(t_common_data *data, t_data_type type);
void				ft_message(t_philo *philo, t_message_type type);
int	ft_get_last_meal(int id, t_common_data *data);


#endif