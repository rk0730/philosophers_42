#include "philo.h"

// idが奇数なら左から取る、偶数なら右から取る
void	ft_get_fork(t_philo *philo)
{
	RKITAO("fork start %d\n", philo->id);
	int l = pthread_mutex_trylock(philo->l_fork);
	int r = pthread_mutex_trylock(philo->r_fork);
	printf("%d l_fork %d r_fork %d\n",philo->id, l, r);
	if (philo->id % 2 == 1)
	{
		RKITAO("lock l_fork\n");
		pthread_mutex_lock(philo->l_fork);
	}
	else
	{
		RKITAO("lock r_fork\n");
		pthread_mutex_lock(philo->r_fork);
	}
	RKITAO("first fork\n");
	ft_message(philo, FIRST_FORK);
	if (philo->id % 2 == 1)	
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	RKITAO("second fork\n");
	ft_message(philo, SECOND_FORK);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	RKITAO("%d start\n", philo->id);
	while (1)
	{
		RKITAO("aa\n");
		ft_get_fork(philo);
		RKITAO("fork\n");
		philo->last_meal_time = ft_get_time(philo->data);
		usleep(ft_get_args(philo->data, TIME_TO_EAT) * 1000);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		ft_message(philo, SLEEP);
		usleep(ft_get_args(philo->data, TIME_TO_SLEEP) * 1000);
		ft_message(philo, THINK);
		RKITAO("break\n");
		break;
	}
	return (NULL);
}
