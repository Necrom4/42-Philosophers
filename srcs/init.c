/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 14:09:07 by dferreir          #+#    #+#             */
/*   Updated: 2023/05/17 10:46:58 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	bro_vars_filler(t_philo *ph)
{
	int	i;

	i = -1;
	ph->bro = malloc(ph->nb_philo * sizeof(t_bro));
	while (++i < ph->nb_philo)
	{
		ph->bro[i].n = i + 1;
		ph->bro[i].philo = ph;
		ph->bro[i].times_ate = 0;
		ph->bro[i].last_meal = 0;
		pthread_mutex_init(&(ph->bro[i].l_fork), 0);
		if (i == ph->nb_philo - 1)
			ph->bro[i].r_fork = &ph->bro[0].l_fork;
		else
			ph->bro[i].r_fork = &ph->bro[i + 1].l_fork;
	}
}

void	global_vars_filler(t_philo *ph, int argc, char **argv)
{
	ph->start = get_time();
	ph->nb_philo = ft_atoi(argv[1]);
	ph->ttd = ft_atoi(argv[2]);
	ph->tte = ft_atoi(argv[3]);
	ph->tts = ft_atoi(argv[4]);
	if (argc == 6)
		ph->times_to_eat = ft_atoi(argv[5]);
	else
		ph->times_to_eat = -1;
	ph->everyone_ate = 0;
	ph->dead = 0;
}

void	init(t_philo *ph, int argc, char **argv)
{
	int	i;

	i = -1;
	global_vars_filler(ph, argc, argv);
	pthread_mutex_init(&(ph->writing), 0);
	pthread_mutex_init(&(ph->eat), 0);
	pthread_mutex_init(&(ph->wait), 0);
	bro_vars_filler(ph);
}
