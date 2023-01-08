/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:39:48 by acardona          #+#    #+#             */
/*   Updated: 2023/01/08 01:26:34 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_pid;

static void	fts_flush(t_buff *b, int error)
{
	b->g_c = 0x80;
	(b->i_buff)--;
	if ((b->buff)[b->i_buff] == 0)
	{
		write(1, b->buff, b->i_buff);
		g_pid = 0;
	}
	else
		write(1, b->buff, b->i_buff + 1);
	if (error)
	{
		write(1, "\n===\n/!\\ CONNEXION TO CLIENT LOST /!\\\n===\n", 42);
		g_pid = 0;
	}
	b->i_buff = 0;
}

static void	fts_add_bit(int sig, siginfo_t *info, void *ucontext)
{
	static t_buff	b = {0, {0}, 0x80};

	(void)ucontext;
	if (g_pid && sig && info->si_pid != g_pid)
	{
		kill(info->si_pid, SIGUSR2);
		return ;
	}
	if (sig == SIGUSR1 || sig == SIGUSR2)
	{
		g_pid = info->si_pid;
		if (sig == SIGUSR2)
			b.g_c = ((b.g_c) << 1) + 1;
		else if (sig == SIGUSR1)
			b.g_c = (b.g_c) << 1;
		if (b.g_c & 0x8000)
		{
			b.buff[b.i_buff] = (unsigned char)((b.g_c) & 0xFF);
			b.g_c = 0x80;
			if ((b.buff)[(b.i_buff)++] == 0 || b.i_buff == 2048)
				fts_flush(&b, 0);
		}
	}
	if ((sig != 10 && sig != 12) || kill (info->si_pid, SIGUSR1) == -1)
		fts_flush(&b, 1);
}

int	main(int ac, char **av)
{
	struct sigaction	act;

	(void) av;
	g_pid = 0;
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
		if (g_pid && kill(g_pid, 0))
			fts_add_bit(0, 0, 0);
	return (0);
}

/*
./client 55194 "$(<joli.txt)"

dans .h : buff[1259}


ligne 57 : i_buff == 1259
entre ligne 58 et 59 : usleep(1100);
*/
