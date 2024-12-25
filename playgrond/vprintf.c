#include <stdio.h>
#include <pthread.h>
#include <stdarg.h>
#include <unistd.h>

pthread_mutex_t		g_lock_print;

void lock_print(const char *fmt, ...)
{
	pthread_mutex_lock(&g_lock_print);
	va_list	ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	pthread_mutex_unlock(&g_lock_print);
}

void	*routine(void *arg)
{
	char *str = *(char **)arg;
	lock_print("Hello, %s\n", str);
	return (NULL);
}

int main(void)
{
	pthread_t thread;
	char *str = "world";
	pthread_mutex_init(&g_lock_print, NULL);

	pthread_mutex_lock(&g_lock_print);
	pthread_create(&thread, NULL, routine, &str);
	sleep(3);
	pthread_mutex_unlock(&g_lock_print);
	lock_print("Hello, %s %d\n", "world", 1+1);

	pthread_join(thread, NULL);
	pthread_mutex_destroy(&g_lock_print);
	return (0);
}