/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 12:13:17 by acardona          #+#    #+#             */
/*   Updated: 2022/11/07 12:13:25 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start,
size_t len)
{
	size_t	i;
	size_t	lens;
	char	*sub;

	lens = ft_strlen(s);
	if (start >= lens)
	{
		sub = malloc(sizeof(char));
		if (!sub)
			return (NULL);
		*sub = 0;
		return (sub);
	}
	if (lens - start < len)
		sub = malloc((lens - start + 1));
	else
		sub = malloc(len + 1);
	if (!sub)
		return (NULL);
	i = -1;
	while (s[++i + start] && i < len)
		sub[i] = s[start + i];
	sub[i] = 0;
	return (sub);
}
