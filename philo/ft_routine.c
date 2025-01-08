#include "philo.h"

// 最大でtimeミリ秒まで待機する。ft_is_finishedがtrueの場合はすぐに終わらせる
void	ft_usleep(t_philo *philo, int time)
{
	while (ft_get_time(philo->data) < time && !ft_is_finished(philo->data))
		usleep(50);
}

// idが奇数なら左から取る、偶数なら右から取る
void	ft_get_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
		pthread_mutex_lock(philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	ft_message(philo, FIRST_FORK);
	if (philo->id % 2 == 1)
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	ft_message(philo, SECOND_FORK);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	int		tmp;

	philo = (t_philo *)arg;
	RKITAO("%d start\n", philo->id);
	// 最初の調整待機時間
	int num_of_philo = ft_get_args(philo->data, NUM_OF_PHILO);
	if (num_of_philo % 2 == 0)
	{
		if (philo->id - 1 % 2 == 0)
			usleep(ft_get_args(philo->data, TIME_TO_EAT));
	}
	else
	{
		if (philo->id - 1 % 2 == 0)
			usleep((2 * num_of_philo - philo->id - 1)/(num_of_philo - 1) * ft_get_args(philo->data, TIME_TO_EAT));
		else
			usleep((num_of_philo - philo->id - 1)/(num_of_philo - 1) * ft_get_args(philo->data, TIME_TO_EAT));
	}
	while (1)
	{
		ft_get_fork(philo);
		tmp = ft_get_time(philo->data);
		pthread_mutex_lock(&philo->data->lock_data);
		*philo->my_last_meal_time = tmp;
		pthread_mutex_unlock(&philo->data->lock_data);
		ft_usleep(philo, ft_get_time(philo->data) + ft_get_args(philo->data, TIME_TO_EAT));
		pthread_mutex_lock(&philo->data->lock_data);
		*(philo->my_eat_count) = *(philo->my_eat_count) + 1;
		pthread_mutex_unlock(&philo->data->lock_data);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		ft_message(philo, SLEEP);
		ft_usleep(philo, ft_get_time(philo->data) + ft_get_args(philo->data, TIME_TO_SLEEP));
		ft_message(philo, THINK);
		if (ft_is_finished(philo->data))
		{
			RKITAO("%d end\n", philo->id);
			break ;
		}
	}
	return (NULL);
}
