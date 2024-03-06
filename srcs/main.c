/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:51:17 by dferreir          #+#    #+#             */
/*   Updated: 2023/05/17 14:13:40 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_bro *bro)
{
	pthread_mutex_lock(&(bro->philo->eat));
	print_action(bro, "is eating");
	bro->last_meal = get_time();
	bro->times_ate++;
	pthread_mutex_unlock(&(bro->philo->eat));
	ft_usleep(bro->philo->tte);
	pthread_mutex_unlock(bro->r_fork);
	pthread_mutex_unlock(&(bro->l_fork));
	print_action(bro, "is sleeping");
	ft_usleep(bro->philo->tts);
	print_action(bro, "is thinking");
}

void	*death_status(void *bros)
{
	int		i;
	t_bro	*bro;

	i = -1;
	bro = (t_bro *)bros;
	ft_usleep(bro->philo->ttd + 1);
	pthread_mutex_lock(&(bro->philo->eat));
	pthread_mutex_lock(&(bro->philo->wait));
	if (get_time() - bro->last_meal > bro->philo->ttd)
	{
		print_action(bro, "died");
		bro->philo->dead = 1;
		free_bird(bro->philo);
	}
	pthread_mutex_unlock(&(bro->philo->eat));
	pthread_mutex_unlock(&(bro->philo->wait));
	return (0);
}

void	eating_status(t_bro *bro)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&(bro->philo->eat));
	pthread_mutex_lock(&(bro->philo->wait));
	while (bro->philo->times_to_eat != -1 && ++i < bro->philo->nb_philo
		&& bro->philo->bro[i].times_ate >= bro->philo->times_to_eat);
	if (i == bro->philo->nb_philo && i != -1)
	{
		bro->philo->dead = 1;
		free_bird(bro->philo);
	}
	pthread_mutex_unlock(&(bro->philo->eat));
	pthread_mutex_unlock(&(bro->philo->wait));
}

void	*exec(void *bros)
{
	t_bro		*bro;
	pthread_t	t;

	bro = (t_bro *)bros;
	if (!(bro->n % 2))
		usleep(1000);
	while (!bro->philo->dead)
	{
		pthread_create(&t, 0, death_status, bro);
		eating_status(bro);
		pthread_mutex_lock(&(bro->l_fork));
		print_action(bro, "has taken a fork");
		pthread_mutex_lock(bro->r_fork);
		print_action(bro, "has taken a fork");
		eat(bro);
		pthread_detach(t);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	int		i;
	t_philo	ph;

	i = -1;
	ph.nb_philo = 0;
	args_check(argc, argv);
	init(&ph, argc, argv);
	while (++i < ph.nb_philo)
	{
		pthread_create(&(ph.bro[i].tid), 0, exec, &(ph.bro[i]));
		ph.bro[i].last_meal = get_time();
	}
	while (!ph.dead)
		;
	return (0);
}
