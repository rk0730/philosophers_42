#include "philo.h"

void	ft_init_common_data(t_common_data *data)
{
	int	i;

	//　dataの初期化
	data->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* data->args->num_of_philo);
	data->eat_count = (int *)malloc(sizeof(int) * data->args->num_of_philo);
	data->last_meal_time = (int *)malloc(sizeof(int)
			* data->args->num_of_philo);
	i = 0;
	while (i < data->args->num_of_philo)
	{
		data->eat_count[i] = 0;
		data->last_meal_time[i] = 0;
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	// data->dead = 0;
	data->philos = (t_philo *)malloc(sizeof(t_philo)
			* data->args->num_of_philo);
	data->threads = (pthread_t *)malloc(sizeof(pthread_t)
			* data->args->num_of_philo);
	pthread_mutex_init(&(data->lock_args), NULL);
	pthread_mutex_init(&data->lock_data, NULL);
	pthread_mutex_init(&data->lock_printf, NULL);
	gettimeofday(&data->start_time, NULL);
}

void	ft_cleanup_common_data(t_common_data *data)
{
	int	i;

	i = 0;
	while (i < data->args->num_of_philo)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&(data->lock_args));
	pthread_mutex_destroy(&data->lock_data);
	pthread_mutex_destroy(&data->lock_printf);
	free(data->forks);
	free(data->eat_count);
	free(data->last_meal_time);
	free(data->philos);
	free(data->threads);
	free(data->args);
	free(data);
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
		data->philos[i].my_last_meal_time = &data->last_meal_time[i];
		pthread_create(&(data->threads[i]), NULL, ft_routine,
			&(data->philos[i]));
		i++;
	}
	pthread_mutex_unlock(&(data->lock_args));
}

int	main(int argc, char **argv)
{
	t_common_data	*data;
	int				i;

	data = (t_common_data *)malloc(sizeof(t_common_data));
	RKITAO("debug mode\n");
	if (ft_arg(argc, argv, data) == 1)
		exit(EXIT_FAILURE);
	// philosopherが1人の時
	if (data->args->num_of_philo == 1)
	{
		usleep(data->args->time_to_die * 1000);
		printf("%d 1 died\n", data->args->time_to_die);
		free(data->args);
		free(data);
		return (0);
	}
	ft_init_common_data(data);
	// スレッドを作成する
	RKITAO("before thread\n");
	ft_gen_threads(data);
	RKITAO("after thread\n");
	// スレッドの終了を待つ
	while (!ft_is_finished(data))
	{
		usleep(100); //これを入れないとhelgrindでうまく動かない
	}
	if (ft_is_dead(data) > 0)
	{
		pthread_mutex_lock(&data->lock_printf);
		printf("%u %d died\n", ft_get_time(data), ft_is_dead(data));
		pthread_mutex_unlock(&data->lock_printf);
	}
	i = 0;
	while (i < data->args->num_of_philo)
	{
		// pthread_detach(data->threads[i]);
		pthread_join(data->threads[i], NULL);
		i++;
	}
	ft_cleanup_common_data(data);
	return (0);
}
