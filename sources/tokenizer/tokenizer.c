/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:26:39 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/15 13:25:41 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

static t_token_list	*token_create_node(char *lexeme, int token_type)
{
	t_token_list	*new_token;

	new_token = malloc(sizeof(t_token_list));
	new_token->token.lexeme = lexeme;
	new_token->token.type = token_type;
	new_token->next = NULL;
	return (new_token);
}

void	add_token_to_list(t_token_list **token_list, char *lexeme, \
	int token_type)
{
	t_token_list	*current;

	if (!*token_list)
	{
		*token_list = token_create_node(lexeme, token_type);
		return ;
	}
	current = *token_list;
	while (current->next)
		current = current->next;
	current->next = token_create_node(lexeme, token_type);
}

t_token_list	*token_get_sublist(t_token_list *token_lst, int start, \
	int lst_len)
{
	int				i;
	t_token_list	*sublist;
	t_token_list	*aux;

	i = 0;
	sublist = NULL;
	aux = token_lst;
	while (aux && i < start)
	{
		aux = aux->next;
		i++;
	}
	i = 0;
	while (aux && i < lst_len)
	{
		add_token_to_list(&sublist, ft_strdup(aux->token.lexeme), \
			aux->token.type);
		aux = aux->next;
		i++;
	}
	return (sublist);
}

void	token_final_state(t_aux_token *aux, t_token_list **token_list, \
	char *str)
{
	if (token_state_requires_backtrack(aux->state))
	{
		aux->i -= 1;
		aux->lexeme_length -= 1;
	}
	aux->token_type = get_token_type(aux->state);
	if (aux->token_type == WORD)
		aux->lexeme = ft_substr(str, aux->i - (aux->lexeme_length - 1), \
		aux->lexeme_length);
	else
		aux->lexeme = NULL;
	add_token_to_list(token_list, aux->lexeme, aux->token_type);
	aux->lexeme_length = 0;
	aux->state = 1;
}

t_token_list	*get_token_list(char *str)
{
	t_token_list	*token_list;
	t_aux_token		aux;

	if (!str)
		return (NULL);
	ft_bzero(&aux, sizeof(t_aux_token));
	aux.state = 1;
	aux.str_length = ft_strlen(str);
	token_list = NULL;
	while (aux.i <= aux.str_length)
	{
		aux.state = token_get_next_state(aux.state, str[aux.i]);
		if (aux.state != 1)
			aux.lexeme_length += 1;
		if (aux.state == -1)
		{
			token_clear_list(&token_list);
			break ;
		}
		if (token_state_is_final(aux.state))
			token_final_state(&aux, &token_list, str);
		aux.i++;
	}
	return (token_list);
}
