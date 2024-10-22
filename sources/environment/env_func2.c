/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_func2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:08:11 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/15 13:04:34 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/environment.h"

void	env_clear_list(t_env **head)
{
	if (head && *head)
	{
		env_clear_list(&(*head)->next);
		free((*head)->name);
		free((*head)->value);
		free((*head));
		*head = NULL;
	}
}

int	att_existing_value(t_env *head, char *name, char *value)
{
	t_env	*temp;

	temp = head;
	while (temp != NULL && name)
	{
		if (ft_strncmp(temp->name, name, -1) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

char	*search_value(t_env *head, char *name)
{
	t_env	*temp;

	temp = head;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->name, name, -1) == 0)
			return (ft_strdup(temp->value));
		temp = temp->next;
	}
	return (ft_strdup(""));
}

int	envp_list_size(t_env *head)
{
	int		i;
	t_env	*aux;

	i = 0;
	aux = head;
	while (aux)
	{
		i++;
		aux = aux->next;
	}
	return (i);
}

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		free(envp[i]);
		i++;
	}
	if (envp)
		free(envp);
}
