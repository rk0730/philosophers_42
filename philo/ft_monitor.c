#include "philo.h"

// 誰かが死んでいるなら、その人のidを返す
int	ft_is_dead(t_common_data *data)
{
	int	num_of_philo;
	int	i;

	// lock_printf("before get_args\n");
	num_of_philo = ft_get_args(data, NUM_OF_PHILO);
	// lock_printf("num of philo: %d\n", num_of_philo);
	i = 0;
	while (i < num_of_philo)
	{
		if (ft_get_time(data) - data->philos[i].last_meal_time > ft_get_args(data, TIME_TO_DIE))
			return (i+1);
		i++;
	}
	return (0);
}

// 誰かが死んでいる、あるいは全員規定回数食べ切っているかどうか確認する
int	ft_is_finished(t_common_data *data)
{
	int	result;
	int	i;

	result = 0;
	if (ft_is_dead(data) > 0)
		result = 1;
	if (ft_get_args(data, NUM_PHILO_MUST_EAT) != -1)
	{
		i = 0;
		pthread_mutex_lock(&data->lock_data);
		while (i < ft_get_args(data, NUM_OF_PHILO))
		{
			if (data->eat_count[i] < data->args->num_philo_must_eat)
				break ;
			i++;
		}
		pthread_mutex_unlock(&data->lock_data);
		if (i == ft_get_args(data, NUM_OF_PHILO))
			result = 1;
	}
	return (result);
}
