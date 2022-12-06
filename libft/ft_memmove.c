/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:06:53 by acardona          #+#    #+#             */
/*   Updated: 2022/11/15 12:49:40 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*usrc;
	unsigned char	*udest;

	usrc = (unsigned char *) src;
	udest = (unsigned char *) dest;
	if (usrc < udest)
		while (n--)
			udest[n] = usrc[n];
	else
		while (n--)
			*udest++ = *usrc++;
	return (dest);
}
