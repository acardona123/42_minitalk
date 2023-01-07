/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:39:48 by acardona          #+#    #+#             */
/*   Updated: 2023/01/07 23:35:13 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	pid;

static void	fts_flush(unsigned char buff[2048], size_t *i_b, unsigned int *g_c)
{
	*g_c = 0x80;
	if (buff[*i_b] == 0)
	{
		write(1, buff, *i_b);
		pid = 0;
	}
	else
	{
		write(1, buff, *i_b + 1);
	}
	*i_b = -1;
}
static void	fts_

static void	fts_add_bit(int sig, siginfo_t *info, void *ucontext)
{
	static size_t			i_buff = 0;
	static unsigned char	buff[2048] = {0};
	static unsigned int		g_c = 0x80;

	(void)ucontext;
	if (sig == SIGUSR1 || sig == SIGUSR2)
	{
		pid = info->si_pid;
		if (sig == SIGUSR2)
			g_c = (g_c << 1) + 1;
		else if (sig == SIGUSR1)
			g_c = g_c << 1;
		if (g_c & 0x8000)
		{
			buff[i_buff] = (unsigned char)(g_c & 0xFF);
			g_c = 0x80;
			if (buff[i_buff] == 0 || i_buff == 2047)
				fts_flush(buff, &i_buff, &g_c);
			i_buff++;
		}
	}
	if ((sig != SIGUSR1 && sig != SIGUSR2)
		|| kill (info->si_pid, SIGUSR1) == -1)
	{
		fts_flush(buff, &i_buff, &g_c);
		pid = 0;
		i_buff++;
		write(1, "\n===\n/!\\ CONNEXION TO CLIENT LOST /!\\\n===\n", 42);
	}
}

int	main(int ac, char **av)
{
	struct sigaction	act;

	(void) av;
	pid = 0;
	if (ac != 1)
		return (0);
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &fts_add_bit;
	write(1, "PID : ", 6);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		if (pid && kill(pid, 0))
			fts_add_bit(0, 0, 0);
	return (0);
}

/*
./client 55194 "$(<joli.txt)"

ligne 22 : 1259
ligne 33 : i_buff == 1258
entre ligne 37 et 38 : usleep(1100);
*/
