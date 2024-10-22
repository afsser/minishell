/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:07:51 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/15 13:09:02 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/expander.h"
#include "../../includes/environment.h"
#include "../../includes/executor.h"

static void	update_envp(char *name, char *value, t_env *envs)
{
	t_env	*tmp;

	tmp = envs;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, name, -1) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
}

static void	add_envp(char *name, char *value, t_env *envs)
{
	t_env	*new;
	t_env	*tmp;

	new = malloc(sizeof(t_env));
	new->name = ft_strdup(name);
	new->value = ft_strdup(value);
	new->next = NULL;
	tmp = envs;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	set_arg(char *arg, int idx, t_env *envs)
{
	int		ret_code;
	char	*name;
	char	*value;

	ret_code = 0;
	name = ft_substr(arg, 0, idx);
	value = ft_substr(arg, idx + 1, ft_strlen(arg) - idx);
	if (name && name[0] && value && key_is_valid(name))
	{
		if (key_exist(name, envs))
			update_envp(name, value, envs);
		else
			add_envp(name, value, envs);
	}
	else
	{
		export_print_error_message(arg);
		ret_code = 1;
	}
	free(name);
	free(value);
	return (ret_code);
}

int	select_arg(char *arg, t_minishell *data)
{
	int	i;
	int	ret_code;

	i = 0;
	ret_code = 0;
	while (arg[i] && arg[i] != '=')
		i++;
	if (arg[i] == '=')
		ret_code = set_arg(arg, i, data->envs);
	else if (key_is_valid(arg))
		env_insert_node(&data->envs, arg, NULL);
	else if (arg[i] == '\0' && !key_is_valid(arg))
	{
		export_print_error_message(arg);
		ret_code = 1;
	}
	return (ret_code);
}

int	builtin_export(char **argv, t_minishell *data)
{
	int		i;
	int		ret_code;

	i = 1;
	ret_code = 0;
	if (!argv[1])
		print_sorted_envp(data);
	else
	{
		while (argv[i])
		{
			ret_code = select_arg(argv[i], data);
			i++;
		}
	}
	return (ret_code);
}
