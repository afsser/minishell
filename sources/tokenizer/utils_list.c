/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:53:03 by educastro         #+#    #+#             */
/*   Updated: 2024/10/15 13:25:48 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

void	token_join_lists(t_token_list **dest, t_token_list *source)
{
	t_token_list	*aux;

	aux = source;
	while (aux)
	{
		add_token_to_list(dest, ft_strdup(aux->token.lexeme), aux->token.type);
		aux = aux->next;
	}
}

int	token_list_size(t_token_list *token_list)
{
	int				i;
	t_token_list	*aux;

	i = 0;
	aux = token_list;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}

void	token_back_one_node(t_token_list *tok_lst, t_token_list **node_to_back)
{
	t_token_list	*aux;

	aux = tok_lst;
	while (aux && aux->next != *node_to_back)
		aux = aux->next;
	*node_to_back = aux;
}

t_token_list	*invert_list(t_token_list *head)
{
	t_token_list	*rest;

	if (head == NULL || head->next == NULL)
		return (head);
	rest = invert_list(head->next);
	head->next->next = head;
	head->next = NULL;
	return (rest);
}

t_token_list	*token_get_node_index(t_token_list *token_list, int index)
{
	int				i;
	t_token_list	*aux;

	i = 0;
	aux = token_list;
	while (aux && i < index)
	{
		aux = aux->next;
		i++;
	}
	return (aux);
}
