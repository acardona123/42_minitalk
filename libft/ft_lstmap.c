/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acardona <acardona@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 13:54:46 by acardona          #+#    #+#             */
/*   Updated: 2022/11/10 18:22:28 by acardona         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *),
void (*del)(void *))
{
	t_list	*dest_init;
	t_list	*scr_elem;
	t_list	*dest_elem;

	if (!lst || !f)
		return (NULL);
	dest_init = ft_lstnew((*f)(lst->content));
	if (!dest_init)
		return (NULL);
	scr_elem = lst->next;
	while (scr_elem)
	{
		dest_elem = ft_lstnew((*f)(scr_elem->content));
		if (!dest_elem)
		{
			ft_lstclear(&dest_init, del);
			return (NULL);
		}
		ft_lstadd_back(&dest_init, dest_elem);
		scr_elem = scr_elem->next;
	}
	return (dest_init);
}
