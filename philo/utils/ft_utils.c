#include "philo.h"

int	ft_isdigit(int c)
{
	if (c < -1 || c > 255)
		return (0);
	if ('0' <= (unsigned char)c && (unsigned char)c <= '9')
		return (1);
	else
		return (0);
}

int	ft_is_all_digit(char *str)
{
	size_t	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	return (str[i] == '\0');
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] == s2[i] && s1[i] != '\0' && i < n - 1)
	{
		i++;
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

static int	ft_atoi_helper(const char *start)
{
	size_t	digit_len;

	digit_len = 0;
	while (ft_isdigit(start[digit_len]))
		digit_len++;
	if (digit_len > 10)
		return (1);
	if (digit_len == 10 && ft_strncmp(start, "2147483647", 10) > 0)
		return (1);
	return (0);
}

int	ft_atoi(const char *str)
{
	int sign;
	int result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (9 <= *str && *str <= 13))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str == '0')
		str++;
	if (ft_atoi_helper(str))
	{
		return (-1 * (sign == 1));
	}
	while (*str && ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}