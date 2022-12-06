/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:12:26 by acardona          #+#    #+#             */
/*   Updated: 2022/11/11 17:02:35 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		last;
	char	cc;

	if (!s)
		return (NULL);
	cc = (char) c;
	i = 0;
	last = -1;
	while (s[i])
	{
		if (s[i] == cc)
			last = i;
		i++;
	}
	if (cc == 0)
		last = i;
	if (last != -1)
		return ((char *)s + last);
	return (NULL);
}
