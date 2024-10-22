/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 15:43:55 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/10 20:45:19 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	builtin_env(t_minishell *data)
{
	t_env	*tmp;

	tmp = data->envs;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "?", -1) != 0)
		{
			if (tmp->value)
				printf("%s=%s\n", tmp->name, tmp->value);
		}
		tmp = tmp->next;
	}
	return (0);
}
