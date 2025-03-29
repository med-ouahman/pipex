/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 06:59:40 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/22 08:05:23 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_f(int *fd)
{
	if (*fd < 0)
		return ;
	close(*fd);
	*fd = -1;
}

void	clean(t_pipex *pipex)
{
	close_f(&pipex->fd1);
	close_f(&pipex->fd2);
	if (pipex->heredoc)
	{
		unlink(pipex->heredoc);
		close_f(&pipex->fds[0]);
		close_f(&pipex->fds[1]);
	}
}

void	error(int code, char *message)
{
	if (message)
		ft_putstr_fd(message, 2);
	exit(code);
}

void	error_type(void)
{
	if (errno == ENOENT)
		return (ft_putstr_fd("command not found\n", 2), exit(127));
	if (errno == EACCES)
		return (ft_putstr_fd("Permission denied\n", 2), exit(126));
	if (errno == ENOMEM)
		return (ft_putstr_fd("memory error\n", 2), exit(1));
	exit(EXIT_FAILURE);
}

void	handle_exit(int status)
{
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		exit(WTERMSIG(status) + 128);
}
