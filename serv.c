#include "minitalk.h"

unsigned int	g_c;

void	ft_add_bit(int sig, siginfo_t *info, void *ucontext)
{
	if (sig == SIGUSR2)
		g_c = (g_c << 1) + 1;
	else if (sig == SIGUSR1)
		g_c = g_c << 1;
	sleep(0.0001);
	kill (info->si_pid, SIGUSR1);
}

int	main(int ac, char **av)
{
	size_t				i_buff;
	unsigned char		buff[1024];
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &ft_add_bit;
	if (ac != 1)
		return (0);
	printf("%d\n", getpid());//============
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	i_buff = 0;
	g_c = 0xFF;
	while (1)
	{
		pause();
		if (g_c & 0x8000)
		{
			buff[i_buff] = (unsigned char)(g_c & 0xFF);
			g_c = 0xFF;
			if (buff[i_buff] == 0 || i_buff == 1024)
			{
				write(1, buff, i_buff);
				i_buff = -1;
			}
			i_buff++;
		}
	}
	return (0);
}
