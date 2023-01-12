/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:39:45 by acardona          #+#    #+#             */
/*   Updated: 2023/01/12 20:48:18 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

long long int	g_pid;

static int	fts_print_error(int err)
{	
	write(1, "\n\e[31m", 6);
	if (err == 1)
		write(1, "Signal received from a process diffent of the server.", 53);
	else if (err == 2)
		write(1, "Server currently used by another client, try later.", 51);
	else if (err == 3)
		write(1, "/!\\ Server unreachable /!\\", 26);
	else if (err == 4)
		write(1, "Invalid number of arguments.", 28);
	else if (err == 5)
		write(1, "PID <= 0 forbidden", 18);
	write(1, "\n\n\e[0m", 6);
	return (1);
}

static void	ft_check_signal(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (info->si_pid != (g_pid >> 2))
		fts_print_error(1);
	if (sig == SIGUSR2)
	{
		fts_print_error(2);
		g_pid += 3;
	}
	else
		g_pid += 1;
}

static int	ft_send_bits(unsigned char c)
{
	int					mask;
	struct sigaction	act;
	int					timer;

	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &ft_check_signal;
	mask = 0b100000000;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (!(g_pid & 2) && mask > 1)
	{
		mask = mask >> 1;
		if (kill(g_pid >> 2, SIGUSR1 + ((mask & c) != 0) * 2) == -1)
			return (fts_print_error(3));
		timer = -2147483648;
		while (++timer < 2147483647 && g_pid != -1 && !(g_pid & 1))
		{
		}
		if (timer == 2147483647)
			return (fts_print_error(2 + (g_pid != -1)));
		g_pid -= 1;
	}
	return (0);
}

int	main(int ac, char **av)
{
	char	*str;
	size_t	i;

	if (ac != 3)
		return (fts_print_error(4));
	g_pid = ft_atoi(av[1]);
	if (g_pid <= 0)
		return (fts_print_error(5));
	g_pid <<= 2;
	str = av[2];
	i = -1;
	while (str[++i])
		if (ft_send_bits((unsigned char) str[i]) || (g_pid & 2))
			return (1);
	if (ft_send_bits(0))
		return (1);
	write(1, "\n\e[32m==== MESSAGE RECIEVED ====\e[0m\n\n", 38);
	return (0);
}
