/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:39:45 by acardona          #+#    #+#             */
/*   Updated: 2023/01/07 22:21:38 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

long long int	g_pid;

static void	ft_check_signal(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	(void)sig;
	if (info->si_pid != (g_pid >> 1))
	{
		write(1, "Signal received from a process diffent of the server.\n", 54);
		return ;
	}
	g_pid += 1;
}

static int	ft_send_bits(unsigned char c)
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
		{
			if (kill(g_pid >> 1, SIGUSR2) == -1)
				return (write(1, "Error : imposible to send message.\n", 35));
		}
		else if (kill(g_pid >> 1, SIGUSR1) == -1)
			return (write(1, "Error : imposible to send message.\n", 35));
		while (!(g_pid & 1))
			if (kill(g_pid >> 1, 0))
				return (write(1, "Server connexion lost.\n", 23));
		g_pid -= 1;
	}
	return (0);
}

int	main(int ac, char **av)
{
	char	*str;
	size_t	i;

	if (ac != 3)
	{
		write(1, "Invalid number of arguments.\n", 29);
		return (0);
	}
	g_pid = (long long int) ft_atoi(av[1]);
	if (g_pid == -1)
	{
		write(1, "PID = -1 forbidden", 17);
		return (1);
	}
	g_pid <<= 1;
	str = av[2];
	i = -1;
	write(1, "ok\n", 3);//
	while (str[++i])
		if (ft_send_bits((unsigned char) str[i]))
			return (1);
	if (ft_send_bits(0))
		return (1);
	write(1, "\n==== MESSAGE RECU ====\n\n", 25);
	return (0);
}
