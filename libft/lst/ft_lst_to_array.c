/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_array.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:34:24 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/09 17:34:42 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	*select_content(void *content);

void	*ft_lst_to_array(t_list *lst)
{
	return (ft_lst_to_array_choice(lst, select_content));
}

void	*ft_lst_to_array_choice(t_list *lst, void *(*selection)(void *))
{
	size_t	size;
	void	**array;

	if (lst == NULL)
		return (NULL);
	size = ft_lstsize(lst);
	array = ft_calloc(size + 1, sizeof(void *));
	size = 0;
	while (lst != NULL)
	{
		array[size] = selection(lst->content);
		size++;
		lst = lst->next;
	}
	return (array);
}

static void	*select_content(void *content)
{
	return (content);
}
