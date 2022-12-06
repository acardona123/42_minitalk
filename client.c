#include "minitalk.h"

int g_pid;

void	ft_check_signal(int sig, siginfo_t *info, void *ucontext)
{
	if (info->si_pid != g_pid)
		exit (1);
}

int	ft_send_bits(unsigned char c)
{
	unsigned char		mask;
	struct sigaction	act;

	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_SIGINFO;
	act.sa_sigaction = &ft_check_signal;
	sigaction(SIGUSR1, &act, NULL);
	mask = 0b10000000;
	while (mask)
	{
		if (mask & c)
			kill(g_pid, SIGUSR2);
		else
			kill(g_pid, SIGUSR1);
		mask = mask >> 1;
		pause();
		sleep(0.0001);
	}
}

int	main(int ac, char **av)
{
	char				*str;
	size_t				i;
	if (ac != 3)
	{
		printf("Nombre d'arguments invalide\n");
		return (0);
	}
	g_pid = ft_atoi(av[1]);//
	str = av[2];
	i = -1;
	while (str[++i])
	{
		//printf("_C char #%ld\n", i);
		ft_send_bits((unsigned char)str[i]);
		sleep(0.5);
	}
	ft_send_bits(0);
	write(1, "\n==== MESSAGE RECU ====\n", 24);
	return (0);
}
