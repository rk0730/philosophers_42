#include "philo.h"

int	ft_get_args(t_common_data *data, t_data_type type)
{
	int	result;

	while (pthread_mutex_trylock(&(data->lock_args)))
	{
		sleep(10);
		// printf("----lock_args %d\n", pthread_mutex_trylock(&(data->lock_args)));
	}
	pthread_mutex_lock(&(data->lock_args));
	if (type == NUM_OF_PHILO)
		result = data->args->num_of_philo;
	else if (type == TIME_TO_DIE)
		result = data->args->time_to_die;
	else if (type == TIME_TO_EAT)
		result = data->args->time_to_eat;
	else if (type == TIME_TO_SLEEP)
		result = data->args->time_to_sleep;
	else if (type == NUM_PHILO_MUST_EAT)
		result = data->args->num_philo_must_eat;
	else
	{
		result = -1;
		printf("error in ft_get_args");
	}
	pthread_mutex_unlock(&(data->lock_args));
	return (result);
}

// startからの経過時間（ミリ秒）を返す
int	ft_get_time(t_common_data *data)
{
	struct timeval	now;
	int				result;

	gettimeofday(&now, NULL);
	pthread_mutex_lock(&data->lock_data);
	result = (now.tv_sec - data->start_time.tv_sec) * 1000 + (now.tv_usec
			- data->start_time.tv_usec) / 1000;
	pthread_mutex_unlock(&data->lock_data);
	return (result);
}

void	ft_message(t_philo *philo, t_message_type type)
{
	int	time;

	time = ft_get_time(philo->data);
	RKITAO("ft_is_finished %d at %d\n", ft_is_finished(philo->data), ft_get_time(philo->data));
	if (ft_is_finished(philo->data) == 0)
	{
		if (type == FIRST_FORK || type == SECOND_FORK)
			printf("%u %d has taken a fork\n", time, philo->id);
		if (type == SECOND_FORK)
			printf("%u %d is eating\n", time, philo->id);
		if (type == SLEEP)
			printf("%u %d is sleeping\n", time, philo->id);
		if (type == THINK)
			printf("%u %d is thinking\n", time, philo->id);
	}
}
