/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nasser <nasser@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:07:26 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/16 02:35:11 by nasser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	int	exec_builtin(char *cmd, char **argv, t_minishell *data)
{
	int	ret_code;

	ret_code = 0;
	if (ft_strncmp(cmd, "echo", -1) == 0)
		ret_code = builtin_echo(argv);
	else if (ft_strncmp(cmd, "cd", -1) == 0)
		ret_code = builtin_cd(argv, data);
	else if (ft_strncmp(cmd, "pwd", -1) == 0)
		ret_code = builtin_pwd();
	else if (ft_strncmp(cmd, "export", -1) == 0)
		ret_code = builtin_export(argv, data);
	else if (ft_strncmp(cmd, "unset", -1) == 0)
		ret_code = builtin_unset(argv, &data->envs);
	else if (ft_strncmp(cmd, "env", -1) == 0)
		ret_code = builtin_env(data);
	else if (ft_strncmp(cmd, "exit", -1) == 0)
		ret_code = builtin_exit(argv, data);
	return (ret_code);
}

static void	handle_redirections(t_tree *tree, t_minishell *data, \
	int *fd_redir)
{
	char	*cmd;

	cmd = expand_string(tree->left->command->token.lexeme, data->envs);
	*fd_redir = open_redir(cmd, tree->type);
	free(cmd);
}

static int	ft_builtins(t_tree *tree, t_minishell *data, \
	t_builtin *builtin)
{
	int	i;
	int	ret_code;

	i = 0;
	builtin->args_num = token_list_size(tree->command);
	builtin->argv = malloc((builtin->args_num + 1) * sizeof(char *));
	builtin->argv[builtin->args_num] = NULL;
	while (i < builtin->args_num)
	{
		builtin->argv[i] = expand_string(token_get_node_index(tree->command, \
			i)->token.lexeme, data->envs);
		i++;
	}
	builtin->cmd = builtin->argv[0];
	ret_code = exec_builtin(builtin->cmd, builtin->argv, data);
	free_envp(builtin->argv);
	return (ret_code);
}

int	process_redirections(t_tree *tree, t_minishell *data)
{
	t_builtin	builtin;

	builtin.ret_code = 0;
	if (tree->type >= REDIRECT_INPUT && tree->type <= REDIRECT_OUTPUT_APPEND)
	{
		handle_redirections(tree, data, &builtin.fd_redir);
		if (builtin.fd_redir == -1)
		{
			perror(tree->left->command->token.lexeme);
			return (1);
		}
		if (tree->type == REDIRECT_INPUT)
			dup2(builtin.fd_redir, STDIN_FILENO);
		else if (tree->type == REDIRECT_OUTPUT || \
			tree->type == REDIRECT_OUTPUT_APPEND)
			dup2(builtin.fd_redir, STDOUT_FILENO);
		builtin.fd_redir = close_fd(builtin.fd_redir);
		builtin.ret_code = process_redirections(tree->right, data);
	}
	else
		builtin.ret_code = ft_builtins(tree, data, &builtin);
	return (builtin.ret_code);
}

int	builtin_process(t_tree *tree, t_minishell *data)
{
	int	ret_code;
	int	prev_fd[2];

	prev_fd[0] = dup(STDIN_FILENO);
	prev_fd[1] = dup(STDOUT_FILENO);
	ret_code = process_redirections(tree, data);
	dup2(prev_fd[0], STDIN_FILENO);
	dup2(prev_fd[1], STDOUT_FILENO);
	close_pipe(prev_fd);
	return (ret_code);
}
