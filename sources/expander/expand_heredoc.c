/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 18:39:48 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/10 20:45:41 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"

static void	skip_invalid_variable(char *str, int *i)
{
	if (!(str[*i] >= '0' && str[*i] <= '9'))
	{
		while (is_valid_var(str[*i]))
			(*i)++;
		if (str[*i] == '$')
			(*i)++;
		if (is_valid_var(str[*i]) == 0)
			(*i)--;
	}
}

static void	expand_variable_heredoc(char *str, int *i, t_str_list **new_str, \
									t_env *envp_list)
{
	int		j;
	char	*key;
	char	*expanded;

	(*i)++;
	if ((str[*i] >= '0' && str[*i] <= '9') || str[*i] == '$'
		|| (is_valid_var(str[*i]) == 0 && str[*i] != '?'))
		skip_invalid_variable(str, i);
	else
	{
		j = 0;
		while (is_valid_var(str[*i]) || (j == 0 && str[*i] == '?'))
		{
			j++;
			(*i)++;
			if (str[(*i) - 1] == '?')
				break ;
		}
		key = ft_substr(str, (*i) - j, j);
		expanded = search_value(envp_list, key);
		add_string_to_list(new_str, expanded);
		free(key);
		free(expanded);
		(*i)--;
	}
}

char	*expand_heredoc(char *str, t_env *envp_list)
{
	int			i;
	char		*expanded;
	t_str_list	*new_str;

	i = 0;
	new_str = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
			expand_variable_heredoc(str, &i, &new_str, envp_list);
		else
			add_letter_list(&new_str, str[i]);
		i++;
	}
	expanded = create_string_from_list(new_str);
	clear_str_list(&new_str);
	return (expanded);
}
