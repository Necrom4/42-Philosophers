/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:24:11 by dferreir          #+#    #+#             */
/*   Updated: 2023/05/17 14:23:04 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_usleep(int ms)
{
	long int	time;

	time = get_time();
	while (get_time() - time < ms)
		usleep(ms * 2);
}

long long	get_time(void)
{
	struct timeval	x;

	gettimeofday(&x, 0);
	return (x.tv_sec * 1000 + x.tv_usec / 1000);
}

size_t	ft_strlen(const char *s)
{
	int	acc;

	acc = 0;
	while (s[acc] != '\0')
		acc++;
	return (acc);
}

int	ft_atoi(const char *str)
{
	int	final;
	int	i;
	int	sign;

	final = 0;
	i = 0;
	sign = 1;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		++i;
	}
	if (str[i] == '-' || str[i] == '+')
		return (0);
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		final *= 10;
		final += str[i] - '0';
		++i;
	}
	return (final * sign);
}

void	print_action(t_bro *bro, char *str)
{
	pthread_mutex_lock(&(bro->philo->writing));
	printf("%lli %d %s\n", get_time() - bro->philo->start, bro->n, str);
	if (!bro->philo->dead)
		pthread_mutex_unlock(&(bro->philo->writing));
}
