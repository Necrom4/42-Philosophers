/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 10:07:14 by dferreir          #+#    #+#             */
/*   Updated: 2023/05/17 14:06:39 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char *c)
{
	while (*c)
	{
		if (*c >= '0' && *c <= '9')
			c++;
		else
			return (0);
	}
	return (1);
}

void	args_check(int argc, char **argv)
{
	if (!(argc == 5 || argc == 6))
		print_err("Wrong number of arguments");
	if (!is_digit(argv[1]) || !is_digit(argv[2])
		|| !is_digit(argv[3]) || !is_digit(argv[4])
		|| ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) <= 0
		|| ft_atoi(argv[3]) <= 0 || ft_atoi(argv[4]) <= 0
		|| (argv[5] && (!is_digit(argv[5]) || (is_digit(argv[5])
					&& ft_atoi(argv[5]) < 0))))
		print_err("Wrong arguments format");
	if (argv[5] && !ft_atoi(argv[5]))
		exit(0);
	return ;
}

void	free_bird(t_philo *ph)
{
	int	i;

	i = -1;
	while (++i < ph->nb_philo)
		pthread_join(ph->bro[i].tid, 0);
	i = -1;
	while (++i < ph->nb_philo)
	{
		pthread_mutex_destroy(&(ph->bro[i].l_fork));
		pthread_mutex_destroy(ph->bro[i].r_fork);
	}
	free(ph->bro);
	pthread_mutex_destroy(&(ph->writing));
	pthread_mutex_destroy(&(ph->eat));
	pthread_mutex_destroy(&(ph->wait));
}
