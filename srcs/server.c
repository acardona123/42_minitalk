/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/07 19:39:48 by acardona          #+#    #+#             */
/*   Updated: 2023/01/12 20:36:26 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_pid;

/*Adds a new element to the list allowing to store msg befor display*/
static int	fts_lst_new(t_buff **b)
{
	t_buff	*new;

	new = malloc(sizeof(t_buff));
	if (!new)
		return (1);
	new->i_buff = 0;
	new->bit_cpt = 0;
	new->next = 0;
	if (!*b)
		new->first = new;
	else
	{
		new->first = (*b)->first;
		(*b)->next = new;
	}
	*b = new;
	return (0);
}

/*Reads and frees all the registered message, error = 1 || 0*/
int	ft_lst_read_free(t_buff **b, int error)
{
	t_buff	*elem;
	t_buff	*tmp;

	if (*b)
	{
		write(1, "\e[32mMessage from pocessus ", 27);
		ft_putnbr_fd(g_pid, 1);
		write(1, " : \n\e[0m", 8);
		elem = (*b)->first;
		while (elem)
		{
			write (1, elem->buff, elem->i_buff);
			tmp = elem->next;
			free(elem);
			elem = tmp;
		}
		*b = 0;
		if (!error)
			write(1, "\n\e[32m==== End of the message ====\e[0m\n\n", 40);
	}
	if (error)
		write (1, "\n\e[31m=== Error detected. Message cut. ===\e[0m\n\n", 48);
	g_pid = 0;
	return (error);
}

/*Add a new 0 or 1 to the msg (to the last char or a new one)*/
int	ft_lst_bit_add(t_buff **b, int bit)
{
	if (!*b && fts_lst_new(b))
		return (ft_lst_read_free(b, 1));
	((*b)->buff)[(*b)->i_buff] = (((*b)->buff)[(*b)->i_buff] << 1) + (bit == 1);
	if (++((*b)->bit_cpt) == 8)
	{
		if (((*b)->buff)[(*b)->i_buff] == 0)
			return (ft_lst_read_free(b, 0));
		if (++((*b)->i_buff) == 2048 && fts_lst_new(b))
			return (ft_lst_read_free(b, 1));
		(*b)->bit_cpt = 0;
	}
	return (0);
}

static void	fts_bit_detect(int sig, siginfo_t *info, void *ucontext)
{
	static t_buff	*b = 0;
	int				bit_added;

	(void)ucontext;
	if (sig == 0)
		return ((void)ft_lst_read_free(&b, 1));
	if (sig != SIGUSR1 && sig != SIGUSR2)
		return ;
	if (g_pid == 0)
		g_pid = info->si_pid;
	else if (g_pid != info->si_pid)
	{
		kill(info->si_pid, SIGUSR2);
		return ;
	}
	bit_added = ft_lst_bit_add(&b, (sig == SIGUSR2));
	if (bit_added)
	{
		if (kill(info->si_pid, SIGUSR2) == -1)
			ft_lst_read_free(&b, 1);
		return ;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		ft_lst_read_free(&b, 1);
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
	act.sa_sigaction = &fts_bit_detect;
	write(1, "PID : ", 6);
	ft_putnbr_fd(getpid(), 1);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
	{
	}
	return (0);
}

/*
./client 55194 "$(<joli.txt)"

dans tous les fichiers remplacer 1048 par 1259
dans l'affichage de la liste ajouter usleep(1100);
*/
