/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:08:45 by acardona          #+#    #+#             */
/*   Updated: 2022/11/07 12:08:47 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	np;

	if (n < 0)
	{
		np = -1 * n;
		write(fd, "-", 1);
	}
	else
		np = n;
	if (np >= 10)
	{
		ft_putnbr_fd(np / 10, fd);
	}
	ft_putchar_fd(np % 10 + '0', fd);
}
