#include "philo.h"

// 最大でtimeミリ秒まで待機する。ft_is_finishedがtrueの場合はすぐに終わらせる
void	ft_usleep(t_philo *philo, int time)
{
	while (ft_get_time(philo->data) < time && !ft_is_finished(philo->data))
		usleep(50);
}

// 自分の方がidのphiloよりもlast_meal_timeが短い（危ない）状態になったらlockする
void	ft_get_fork_h(t_philo *philo, int id, pthread_mutex_t *fork)
{
	while (!ft_is_finished(philo->data)
		&& *philo->my_last_meal_time > ft_get_last_meal(id, philo->data))
		usleep(100);
	pthread_mutex_lock(fork);
}

// idが奇数なら左から取る、偶数なら右から取る
void	ft_get_fork(t_philo *philo)
{
	int	l_id;
	int	r_id;

	if (philo->id == 1)
		l_id = ft_get_args(philo->data, NUM_OF_PHILO);
	else
		l_id = philo->id - 1;
	if (philo->id == ft_get_args(philo->data, NUM_OF_PHILO))
		r_id = 1;
	else
		r_id = philo->id + 1;
	if (philo->id % 2 == 1)
		ft_get_fork_h(philo, l_id, philo->l_fork);
	else
		ft_get_fork_h(philo, r_id, philo->r_fork);
	ft_message(philo, FIRST_FORK);
	if (philo->id % 2 == 1)
		ft_get_fork_h(philo, r_id, philo->r_fork);
	else
		ft_get_fork_h(philo, l_id, philo->l_fork);
	ft_message(philo, SECOND_FORK);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;
	int		tmp;

	philo = (t_philo *)arg;
	RKITAO("%d start\n", philo->id);
	// 最初の調整待機時間
	if (philo->id % 2 == 1)
		ft_usleep(philo, ft_get_args(philo->data, TIME_TO_EAT) / 2);
	while (1)
	{
		ft_get_fork(philo);
		if (ft_is_finished(philo->data))
		{
			pthread_mutex_unlock(philo->l_fork);
			pthread_mutex_unlock(philo->r_fork);
			RKITAO("%d end\n", philo->id);
			break ;
		}
		tmp = ft_get_time(philo->data);
		pthread_mutex_lock(&philo->data->lock_data);
		*philo->my_last_meal_time = tmp;
		pthread_mutex_unlock(&philo->data->lock_data);
		ft_usleep(philo, ft_get_time(philo->data) + ft_get_args(philo->data,
				TIME_TO_EAT));
		pthread_mutex_lock(&philo->data->lock_data);
		*(philo->my_eat_count) = *(philo->my_eat_count) + 1;
		pthread_mutex_unlock(&philo->data->lock_data);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		ft_message(philo, SLEEP);
		ft_usleep(philo, ft_get_time(philo->data) + ft_get_args(philo->data,
				TIME_TO_SLEEP));
		ft_message(philo, THINK);
	}
	return (NULL);
}
