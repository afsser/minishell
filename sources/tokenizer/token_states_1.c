/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_states_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:11:55 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/15 13:25:31 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

int	get_state_1(char character)
{
	int	state;

	if (character == '(')
		state = 20;
	else if (character == ')')
		state = 30;
	else if (character == '|')
		state = 40;
	else if (character == '&')
		state = 50;
	else if (character == '<')
		state = 60;
	else if (character == '>')
		state = 70;
	else if (character == '\'')
		state = 81;
	else if (character == '\"')
		state = 82;
	else if (character == '\0' || ft_isspace(character))
		state = 1;
	else if (is_metacharacter(character) == 0)
		state = 80;
	else
		state = -1;
	return (state);
}

int	get_state_40(char character)
{
	int	state;

	if (character == '|')
		state = 41;
	else if (character != '|')
		state = 42;
	else
		state = -1;
	return (state);
}

int	get_state_50(char character)
{
	int	state;

	if (character == '&')
		state = 51;
	else if (character != '&')
		state = -1;
	else
		state = -1;
	return (state);
}

int	get_state_60(char character)
{
	int	state;

	if (character == '<')
		state = 61;
	else if (character != '<')
		state = 62;
	else
		state = -1;
	return (state);
}

int	get_state_70(char character)
{
	int	state;

	if (character == '>')
		state = 71;
	else if (character != '>')
		state = 72;
	else
		state = -1;
	return (state);
}
