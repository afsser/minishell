/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_states_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 16:19:51 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/15 13:25:28 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

int	get_state_80(char character)
{
	int	state;

	if (character == '\'')
		state = 81;
	else if (character == '\"')
		state = 82;
	else if (is_metacharacter(character) == 1 || character == '\0')
		state = 83;
	else if (is_metacharacter(character) == 0)
		state = 80;
	else
		state = -1;
	return (state);
}

int	get_state_81(char character)
{
	int	state;

	if (character == '\0')
		state = -1;
	else if (character == '\'')
		state = 80;
	else if (character != '\'')
		state = 81;
	else
		state = -1;
	return (state);
}

int	get_state_82(char character)
{
	int	state;

	if (character == '\0')
		state = -1;
	else if (character == '\"')
		state = 80;
	else if (character != '\"')
		state = 82;
	else
		state = -1;
	return (state);
}
