/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 19:23:34 by fcaldas-          #+#    #+#             */
/*   Updated: 2024/10/15 13:29:48 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	exit_print_error_message(char *message)
{
	int			i;
	int			length;
	char		*line;
	const char	*to_print[] = {"ERROR: exit: ", message, NULL};

	i = 0;
	length = 0;
	while (to_print[i])
		length += ft_strlen(to_print[i++]);
	line = malloc(sizeof(char) * (length + 1));
	i = 1;
	ft_strlcpy(line, to_print[0], length + 1);
	while (to_print[i])
	{
		ft_strlcat(line, to_print[i], length + 1);
		i++;
	}
	ft_putendl_fd(line, STDERR_FILENO);
	free(line);
}

int	exit_arg_valid(char *arg)
{
	int	i;

	i = 0;
	while (isspace(arg[i]))
		i++;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			exit_print_error_message("numeric argument required");
			return (0);
		}
		i++;
	}
	return (1);
}

int	builtin_exit(char **argv, t_minishell *data)
{
	int		ret_code;
	int		args_num;
	char	*ret_code_str;

	ret_code = 0;
	args_num = 0;
	while (argv[args_num])
		args_num++;
	if (args_num > 2)
	{
		exit_print_error_message("too many arguments");
		return (1);
	}
	if (args_num == 1)
	{
		ret_code_str = search_value(data->envs, "?");
		ret_code = ft_atoi(ret_code_str);
		free(ret_code_str);
	}
	else if (!exit_arg_valid(argv[1]))
		ret_code = 2;
	ft_putstr_fd("exit\n", STDOUT_FILENO);
	g_signal = -1;
	return (ternary(args_num == 1, ret_code, \
		ternary(ret_code == 2, 2, ft_atoi(argv[1]))));
}
