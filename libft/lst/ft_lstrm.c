/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstrm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 16:25:31 by fcaldas-          #+#    #+#             */
/*   Updated: 2024/10/15 12:36:26 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

t_list	*ft_lstrm(t_list *lst, t_list *rm_element, void (*del)(void *))
{
	t_list	*head;
	t_list	*prev;

	if (lst == rm_element)
	{
		head = lst->next;
		ft_lstdelone(lst, del);
		return (head);
	}
	head = lst;
	while (lst != NULL)
	{
		prev = lst;
		lst = lst->next;
		if (lst == rm_element)
		{
			prev->next = lst->next;
			ft_lstdelone(lst, del);
			break ;
		}
	}
	return (head);
}
