/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:03:26 by acardona          #+#    #+#             */
/*   Updated: 2022/11/15 12:30:33 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;
	size_t	i;
	size_t	tot;

	ptr = NULL;
	if (size == 0 || nmemb == 0 || nmemb > ULLONG_MAX / size)
		return (malloc(0));
	tot = nmemb * size;
	ptr = malloc(tot);
	if (!ptr)
		return (NULL);
	i = 0;
	while (i < tot)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
