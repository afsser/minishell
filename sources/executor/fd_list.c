/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_list.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: edcastro <edcastro@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 21:05:59 by edcastro          #+#    #+#             */
/*   Updated: 2024/10/15 13:34:00 by edcastro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	close_fd(int fd)
{
	if (fd >= 0)
		close(fd);
	return (-1);
}

void	close_pipe(int *pipe_fd)
{
	pipe_fd[0] = close_fd(pipe_fd[0]);
	pipe_fd[1] = close_fd(pipe_fd[1]);
}

void	fd_list_add_fd(t_list **fd_list, int fd)
{
	int		*fd_ptr;
	t_list	*new;

	fd_ptr = malloc(sizeof(int));
	*fd_ptr = fd;
	new = ft_lstnew(fd_ptr);
	ft_lstadd_back(fd_list, new);
}

void	fd_list_close_clear(t_list **fd_list)
{
	t_list	*tmp;

	while (*fd_list)
	{
		close_fd(*((int *)(*fd_list)->content));
		tmp = *fd_list;
		*fd_list = (*fd_list)->next;
		free(tmp->content);
		free(tmp);
	}
}
