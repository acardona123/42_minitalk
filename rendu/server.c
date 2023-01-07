/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:39:48 by acardona          #+#    #+#             */
/*   Updated: 2023/01/07 22:26:39 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

unsigned int	g_c;

static void	fts_flush_buff(unsigned char buff[2048], size_t *len_buff)
{
	g_c = 0x80;
	write(1, buff, *len_buff);
	write(1, "\n\n/!\\ Client unreachable : end of message lost /!\\\n\n", 52);
	*len_buff = -1;
}

static void	ft_add_bit(int sig, siginfo_t *info, void *ucontext)
{
	static size_t			i_buff = 0;
	static unsigned char	buff[2048] = {0};

	(void)ucontext;
	if (sig == SIGUSR2)
		g_c = (g_c << 1) + 1;
	else if (sig == SIGUSR1)
		g_c = g_c << 1;
	if (g_c & 0x8000)
	{
		buff[i_buff] = (unsigned char)(g_c & 0xFF);
		g_c = 0x80;
		if (buff[i_buff] == 0 || i_buff == 2047)
		{
			if (buff[i_buff] == 0)
				write(1, buff, i_buff);
			else
				write(1, buff, i_buff + 1);
			i_buff = -1;
		}
		i_buff++;
	}
	if (kill (info->si_pid, SIGUSR1) == -1)
		fts_flush_buff(buff, &i_buff);
}

int	main(int ac, char **av)
{
	struct sigaction	act;

	(void) av;
	if (ac != 1)
		return (0);
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &ft_add_bit;
	write(1, "PID : ", 6);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	g_c = 0x80;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
	{
	}
	return (0);
}

/*
./client 55194 "$(<joli.txt)"

ligne 22 : 1259
ligne 33 : i_buff == 1258
entre ligne 37 et 38 : usleep(1100);
*/
