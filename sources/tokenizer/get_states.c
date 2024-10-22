/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_states.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 18:44:40 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/15 13:25:20 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

int	get_token_type(int state)
{
	int	type;

	if (state == 20)
		type = OPEN_PARENTHESIS;
	else if (state == 30)
		type = CLOSE_PARENTHESIS;
	else if (state == 41)
		type = OR;
	else if (state == 42)
		type = PIPE;
	else if (state == 51)
		type = AND;
	else if (state == 61)
		type = REDIRECT_HEREDOC;
	else if (state == 62)
		type = REDIRECT_INPUT;
	else if (state == 71)
		type = REDIRECT_OUTPUT_APPEND;
	else if (state == 72)
		type = REDIRECT_OUTPUT;
	else if (state == 83)
		type = WORD;
	else
		type = -1;
	return (type);
}

int	token_state_requires_backtrack(int state)
{
	if (state == 42
		|| state == 62
		|| state == 72
		|| state == 83)
		return (1);
	return (0);
}

int	token_state_is_final(int state)
{
	if (state == 20
		|| state == 30
		|| state == 41 || state == 42
		|| state == 51
		|| state == 61 || state == 62
		|| state == 71 || state == 72
		|| state == 83)
		return (1);
	return (0);
}

int	token_get_next_state(int state, char c)
{
	int	new_state;

	if (state == 1)
		new_state = get_state_1(c);
	else if (state == 40)
		new_state = get_state_40(c);
	else if (state == 50)
		new_state = get_state_50(c);
	else if (state == 60)
		new_state = get_state_60(c);
	else if (state == 70)
		new_state = get_state_70(c);
	else if (state == 80)
		new_state = get_state_80(c);
	else if (state == 81)
		new_state = get_state_81(c);
	else if (state == 82)
		new_state = get_state_82(c);
	else
		new_state = -1;
	return (new_state);
}
