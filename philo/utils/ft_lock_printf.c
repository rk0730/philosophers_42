#include "philo.h"

void	lock_printf(const char *fmt, ...)
{
	pthread_mutex_lock(&g_lock_print);
	va_list	ap;
	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	pthread_mutex_unlock(&g_lock_print);
}
