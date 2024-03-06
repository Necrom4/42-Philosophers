/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dferreir <dferreir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/11 09:50:06 by dferreir          #+#    #+#             */
/*   Updated: 2023/05/17 11:41:56 by dferreir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H

# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

//DEFINITIONS

//STRUCTS

typedef struct s_bro
{
	int				n;
	int				times_ate;
	long long		last_meal;
	pthread_t		tid;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	*r_fork;
	struct s_philo	*philo;
}	t_bro;

typedef struct s_philo
{
	int				nb_philo;
	int				ttd;
	int				tte;
	int				tts;
	int				times_to_eat;
	int				dead;
	int				everyone_ate;
	long long		start;
	t_bro			*bro;
	pthread_mutex_t	eat;
	pthread_mutex_t	writing;
	pthread_mutex_t	wait;
}	t_philo;

//FUNCTIONS

void		*exec(void *bros);

/* utils */
void		ft_usleep(int ms);

long long	get_time(void);

size_t		ft_strlen(const char *s);

int			ft_atoi(const char *str);

void		print_action(t_bro *bro, char *str);

/* checker */
void		args_check(int argc, char **argv);

int			is_digit(char *c);

void		free_bird(t_philo *ph);

/* init */
void		init(t_philo *ph, int argc, char **argv);

/* errors */
int			print_err(char *msg);

#endif
