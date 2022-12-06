/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:01:46 by acardona          #+#    #+#             */
/*   Updated: 2022/11/11 15:27:49 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_iswhitespace(char c)
{
	int	i;

	i = 0;
	while (" \f\n\r\t\v"[i])
		if (c == " \f\n\r\t\v"[i++])
			return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	nb;
	int	neg;
	int	i;

	if (!nptr)
		return (0);
	neg = 1;
	nb = 0;
	i = 0;
	while (ft_iswhitespace(nptr[i]))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			neg = -1;
		i++;
	}
	while (nptr[i] && ft_isdigit(nptr[i]))
	{
		nb = nb * 10 + nptr[i] - '0';
		i++;
	}
	return (neg * nb);
}
