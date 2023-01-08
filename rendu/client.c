/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:39:45 by acardona          #+#    #+#             */
/*   Updated: 2023/01/08 01:24:39 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

long long int	g_pid;

static int	fts_print_error(int err)
{
	if (err == 1)
		write(1, "Signal received from a process diffent of the server.\n", 54);
	else if (err == 2)
		write(1, "Server currently used by another client, try later.\n", 52);
	else if (err == 3)
		write(1, "/!\\ Server unreachable /!\\\n", 27);
	else if (err == 4)
		write(1, "Invalid number of arguments.\n", 29);
	else if (err == 5)
		write(1, "PID = -1 forbidden", 17);
	return (1);
}

static void	ft_check_signal(int sig, siginfo_t *info, void *ucontext)
{
	(void)ucontext;
	if (info->si_pid != (g_pid >> 1))
		fts_print_error(1);
	if (sig == SIGUSR2)
	{
		fts_print_error(2);
		g_pid = -1;
	}
	else
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
	sigaction(SIGUSR2, &act, NULL);
	mask = 0b100000000;
	while (g_pid != -1 && mask > 1)
	{
		mask = mask >> 1;
		if (mask & c)
		{
			if (kill(g_pid >> 1, SIGUSR2) == -1)
				return (fts_print_error(3));
		}
		else if (kill(g_pid >> 1, SIGUSR1) == -1)
			return (fts_print_error(3));
		while (g_pid == -1 || !(g_pid & 1))
			if (g_pid == -1 || kill(g_pid >> 1, 0))
				return (fts_print_error(3 * (g_pid != -1)));
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
	if (g_pid == -1)
		return (fts_print_error(5));
	g_pid <<= 1;
	str = av[2];
	i = -1;
	while (str[++i])
		if (ft_send_bits((unsigned char) str[i]) || g_pid == -1)
			return (1);
	if (ft_send_bits(0))
		return (1);
	write(1, "\n==== MESSAGE RECU ====\n\n", 25);
	return (0);
}
