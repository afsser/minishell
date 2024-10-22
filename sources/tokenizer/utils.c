/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 17:52:58 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/15 13:25:52 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

void	token_clear_list(t_token_list **token_list)
{
	t_token_list	*current;
	t_token_list	*next;

	if (token_list)
	{
		current = *token_list;
		while (current)
		{
			next = current->next;
			if (current->token.lexeme)
				free(current->token.lexeme);
			free(current);
			current = next;
		}
		*token_list = NULL;
	}
}

int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int	is_metacharacter(char character)
{
	if (character == '('
		|| character == ')'
		|| character == '|'
		|| character == '&'
		|| character == '<'
		|| character == '>'
		|| character == '\''
		|| character == '\"'
		|| ft_isspace(character))
		return (1);
	return (0);
}

int	is_an_command_element(t_token_list *node)
{
	if (node && (node->token.type == WORD
			|| node->token.type == PIPE
			|| node->token.type == REDIRECT_INPUT
			|| node->token.type == REDIRECT_HEREDOC
			|| node->token.type == REDIRECT_OUTPUT
			|| node->token.type == REDIRECT_OUTPUT_APPEND))
		return (1);
	return (0);
}
