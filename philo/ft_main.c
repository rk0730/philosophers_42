#include "philo.h"

pthread_mutex_t g_lock_print;

void	ft_init_common_data(t_common_data *data)
{
	int	i;

	//　dataの初期化
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->args->num_of_philo);
	data->eat_count = (int *)malloc(sizeof(int) * data->args->num_of_philo);
	i = 0;
	while (i < data->args->num_of_philo)
	{
		data->eat_count[i] = 0;
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	// data->dead = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo) * data->args->num_of_philo);
	data->threads = (pthread_t *)malloc(sizeof(pthread_t) * data->args->num_of_philo);
	pthread_mutex_init(&(data->lock_args), NULL);
	pthread_mutex_init(&data->lock_data, NULL);
	gettimeofday(&data->start_time, NULL);
}

void	ft_gen_threads(t_common_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&(data->lock_args));
	while (i < data->args->num_of_philo)
	{
		// t_philoの初期化
		data->philos[i].data = data;
		data->philos[i].id = i + 1;
		if (i == 0)
			data->philos[i].l_fork = &data->forks[data->args->num_of_philo - 1];
		else
			data->philos[i].l_fork = &data->forks[i - 1];
		data->philos[i].r_fork = &data->forks[i];
		data->philos[i].my_eat_count = &data->eat_count[i];
		pthread_create(&(data->threads[i]), NULL, ft_routine,
			&(data->philos[i]));
		data->philos[i].last_meal_time = 0;
		i++;
	}
	lock_printf("finish ft_gen_thread\n");
	pthread_mutex_unlock(&(data->lock_args));
}

int	main(int argc, char **argv)
{
	t_common_data	*data;
	int				i;

	pthread_mutex_init(&g_lock_print, NULL);
	data = (t_common_data *)malloc(sizeof(t_common_data));
	RKITAO("debug mode\n");
	if (ft_arg(argc, argv, data) == 1)
		exit(EXIT_FAILURE);
	ft_init_common_data(data);
	// スレッドを作成する
	RKITAO("before thread\n");
	ft_gen_threads(data);
	RKITAO("after thread\n");
	// スレッドの終了を待つ
	while (!ft_is_finished(data))
		(void)argc;
	RKITAO("point1\n");
	if (ft_is_dead(data) > 0)
		lock_printf("%u %d died\n", ft_get_time(data), ft_is_dead(data));
	i = 0;
	while (i < data->args->num_of_philo)
	{
		pthread_detach(data->threads[i]);
		i++;
	}
	pthread_mutex_destroy(&g_lock_print);
	return (0);
}
