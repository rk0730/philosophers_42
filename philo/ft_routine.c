/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_routine.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kitaoryoma <kitaoryoma@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 18:08:53 by kitaoryoma        #+#    #+#             */
/*   Updated: 2024/12/15 19:09:07 by kitaoryoma       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// idが奇数なら左から取る、偶数なら右から取る
void	ft_get_fork(t_philo *philo)
{
	if (philo->id % 2 == 1)
		pthread_mutex_lock(philo->l_fork);
	else
		pthread_mutex_lock(philo->r_fork);
	// メッセージ
	printf("%d has taken first fork\n", philo->id);
	if (philo->id % 2 == 1)	
		pthread_mutex_lock(philo->r_fork);
	else
		pthread_mutex_lock(philo->l_fork);
	// メッセージ
	printf("%d has taken second fork\n", philo->id);
}

void	*ft_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	RKITAO("%d start\n", philo->id);
	ft_get_fork(philo);
	return (NULL);
}
