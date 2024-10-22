/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 17:01:01 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/15 13:34:07 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	sig_handler_heredoc(int signal __attribute__((unused)))
{
	ft_putendl_fd("", STDOUT_FILENO);
	close(STDIN_FILENO);
	g_signal = SIGINT;
}

void	sig_handler_sigint(int signal __attribute__((unused)))
{
	ft_putendl_fd("", STDOUT_FILENO);
	g_signal = SIGINT;
}

void	sig_handler_redo_readline(int signal __attribute__((unused)))
{
	ft_putendl_fd("", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
