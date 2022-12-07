/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:39:45 by acardona          #+#    #+#             */
/*   Updated: 2022/12/07 19:39:46 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_pid;

static void	ft_check_signal(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)sig;
	if (info->si_pid != (g_pid >> 1))
	{
		write(1, "#### PROBLEME ####\n", 19);
		exit (1);
	}
	g_pid += 1;
}

static void	ft_send_bits(unsigned char c)
{
	int					mask;
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &ft_check_signal;
	sigaction(SIGUSR1, &act, NULL);
	mask = 0b100000000;
	while (mask > 1)
	{
		mask = mask >> 1;
		if (mask & c)
			kill(g_pid >> 1, SIGUSR2);
		else
			kill(g_pid >> 1, SIGUSR1);
		while (!(g_pid & 1))
		{
		}
		g_pid -= 1;
	}	
}

int	main(int ac, char **av)
{
	char	*str;
	size_t	i;

	if (ac != 3)
	{
		write(1, "Nombre d'arguments invalide\n", 28);
		return (0);
	}
	g_pid = ft_atoi(av[1]);
	g_pid <<= 1;
	str = av[2];
	i = -1;
	while (str[++i])
		ft_send_bits((unsigned char) str[i]);
	ft_send_bits(0);
	write(1, "\n==== MESSAGE RECU ====\n\n", 25);
	return (0);
}
