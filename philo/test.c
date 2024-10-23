#include <unistd.h>
#include <stdio.h>
#include <pthread.h>
#include <sys/time.h>

struct timeval start, current;

typedef struct routine_arg {//1
	int				n;
	pthread_mutex_t mutex;
}	routine_arg;

void *routine(void *arg)
{
	routine_arg	*r_arg = (routine_arg *)arg;
	long	seconds;
	long	microseconds;

	pthread_mutex_lock(&r_arg->mutex);//3
	r_arg->n++;
	r_arg->n++;
	r_arg->n++;
	usleep(100);
	gettimeofday(&current, NULL); // 現在時刻を取得
	seconds = current.tv_sec - start.tv_sec;
	microseconds = current.tv_usec - start.tv_usec;
	if (microseconds < 0)
	{
		seconds -= 1;
		microseconds += 1000000;
	}
	printf("経過時間: %ld秒 %ldマイクロ秒\n", seconds, microseconds);
	pthread_mutex_unlock(&r_arg->mutex);//4

	return NULL;
}

int main(void)
{
	pthread_t	threads[100000];
	routine_arg	arg;

	gettimeofday(&start, NULL); // プログラム開始時の時刻を取得
	arg.n = 0;
	pthread_mutex_init(&arg.mutex, NULL);//2

	for (int i = 0; i < 100000; i++)
		pthread_create(&threads[i], NULL, routine, &arg);

	for (int i = 0; i < 100000; i++)
		pthread_join(threads[i], NULL);

	printf("n = %d\n", arg.n);

	pthread_mutex_destroy(&arg.mutex);//5
	return 0;
}