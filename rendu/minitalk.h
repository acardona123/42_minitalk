/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:12:53 by acardona          #+#    #+#             */
/*   Updated: 2023/01/07 23:34:03 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <unistd.h>
# include <signal.h>
# include <stdlib.h>

typedef struct s_buff
{
	size_t			i_buff;
	unsigned char	buff[2048];
	unsigned int	g_c;
}	t_buff;

int		ft_atoi(const char *nptr);
void	ft_putnbr_fd(int n, int fd);

#endif
