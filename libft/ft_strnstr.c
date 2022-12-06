/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:11:53 by acardona          #+#    #+#             */
/*   Updated: 2022/11/11 17:02:11 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	lenbig;

	if (!little || !big)
		return (NULL);
	if (little[0] == '\0')
		return ((char *) big);
	j = 0;
	i = 0;
	lenbig = ft_strlen((char *) big);
	while (i < lenbig && i < len)
	{
		while (i + j < len && little[j]
			&& big[i + j] && big[i + j] == little[j])
			j++;
		if (little[j])
			j = 0;
		else
			return ((char *) &big[i]);
		i++;
	}
	return (NULL);
}
