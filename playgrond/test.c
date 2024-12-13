#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

struct timeval start, current;

typedef struct routine_arg {//1
	int				n;
	pthread_t	threads[10000];
	pthread_mutex_t mutex;
}	routine_arg;

void *routine(void *arg)
{
	routine_arg	*r_arg = (routine_arg *)arg;
	long	seconds;
	long	microseconds;

	pthread_mutex_lock(&r_arg->mutex);//3
	r_arg->n++;
	usleep(10);
	gettimeofday(&current, NULL); // 現在時刻を取得
	seconds = current.tv_sec - start.tv_sec;
	microseconds = current.tv_usec - start.tv_usec;
	if (microseconds < 0)
	{
		seconds -= 1;
		microseconds += 1000000;
	}
	// printf("経過時間: %ld秒 %ldマイクロ秒\n", seconds, microseconds);
	if (r_arg->n % 1000 == 0)
		printf("n = %d\n", r_arg->n);
	pthread_mutex_unlock(&r_arg->mutex);//4

	return NULL;
}

int main(void)
{
	pthread_t	threads[10000];
	routine_arg	arg;

	gettimeofday(&start, NULL); // プログラム開始時の時刻を取得
	arg.n = 0;
	arg.threads = threads;
	pthread_mutex_init(&arg.mutex, NULL);//2

	for (int i = 0; i < 10000; i++)
		pthread_create(&threads[i], NULL, routine, &arg);
	
	printf("create end\n");
	sleep(3);
	pthread_mutex_lock(&arg.mutex);
	printf("3 n == %d\n", arg.n);
	pthread_mutex_unlock(&arg.mutex);

	// for (int i = 0; i < 10000; i++){
	// 	pthread_detach(threads[i]);
	// }
	pthread_detach(threads[0]);
	// pthread_join(threads[0], NULL);
	// for (int i = 8500; i < 10000; i++)
	// 	pthread_join(threads[i], NULL);
	pthread_mutex_destroy(&arg.mutex);//5

	printf("n == %d\n", arg.n);
	sleep(3);
	printf("n == %d\n", arg.n);



	return 0;
}