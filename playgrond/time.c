#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

int	main(void)
{
	long	seconds;
	long	microseconds;

	struct timeval start, current;
	gettimeofday(&start, NULL); // プログラム開始時の時刻を取得
	printf("start %ld", start.tv_sec * 1000 + start.tv_usec / 1000);
	while (1)
	{
		gettimeofday(&current, NULL); // 現在時刻を取得
		// 経過時間を計算（秒とマイクロ秒）
		seconds = current.tv_sec - start.tv_sec;
		microseconds = current.tv_usec - start.tv_usec;
		if (microseconds < 0)
		{
			seconds -= 1;
			microseconds += 1000000;
		}
		printf("経過時間: %ld秒 %ldマイクロ秒\n", seconds, microseconds);
		// 1秒待機
		// sleep(1);
		usleep(1000000);
	}
	return (0);
}
