/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkitao <rkitao@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 23:22:48 by rkitao            #+#    #+#             */
/*   Updated: 2024/12/15 00:19:16 by rkitao           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>

#ifdef RKITAO_DEBUG
# define RKITAO(fmt, ...) printf(fmt, ##__VA_ARGS__)
#else
# define RKITAO(fmt, ...)
#endif

#endif