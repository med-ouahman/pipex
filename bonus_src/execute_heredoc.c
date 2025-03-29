/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_heredoc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 03:53:35 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/22 06:42:11 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	heredoc_files(int i, t_pipex *pipex)
{
	if (i != 1)
		return (0);
	if (!access(pipex->outfile, F_OK) && access(pipex->outfile, W_OK))
		return (ft_printf_fd(2, "Permission denied: %s\n", pipex->outfile), 1);
	pipex->fd2 = open(pipex->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (pipex->fd2 < 0)
	{
		ft_printf_fd(2, "No such file or directory: %s\n", pipex->outfile);
		return (1);
	}
	return (0);
}

static void	heredoc_pipes(int i, t_pipex *pipex)
{
	if (i == 0)
	{
		pipex->fd1 = open(pipex->heredoc, O_RDONLY);
		if (pipex->fd1 < 0 || dup2(pipex->fd1, 0) == -1)
			return (clean(pipex), error_type());
		close_f(&pipex->fd1);
		close_f(&pipex->fds[0]);
		if (dup2(pipex->fds[1], 1) == -1)
			return (clean(pipex), error_type());
		close_f(&pipex->fds[1]);
	}
	if (i == 1)
	{
		close_f(&pipex->fds[1]);
		if (dup2(pipex->fds[0], 0) == -1)
			return (clean(pipex), error_type());
		close_f(&pipex->fds[0]);
		if (pipex->fd2 < 0 || dup2(pipex->fd2, 1) == -1)
			return (clean(pipex), error_type());
		close_f(&pipex->fd2);
	}
}

static void	child(int i, t_pipex *pipex, pid_t *pids)
{
	pids[i] = fork();
	if (pids[i] == -1)
		return (clean(pipex), error_type());
	if (pids[i] == 0)
	{
		if (heredoc_files(i, pipex) == 1)
		{
			clean(pipex);
			error(EXIT_FAILURE, NULL);
		}
		else
		{
			heredoc_pipes(i, pipex);
			exec_cmd(pipex->cmds[i], pipex);
		}
	}
}

void	execute_heredoc(t_pipex *pipex)
{
	int		i;
	int		status;
	pid_t	pids[2];

	i = 0;
	pipex->fd1 = -1;
	pipex->fd2 = -1;
	pipex->fds[0] = -1;
	pipex->fds[1] = -1;
	write_heredoc(pipex);
	if (pipe(pipex->fds) < 0)
		error_type();
	child(0, pipex, pids);
	child(1, pipex, pids);
	close(pipex->fds[0]);
	close(pipex->fds[1]);
	if (waitpid(pids[0], NULL, 0) == -1)
		error_type();
	if (waitpid(pids[1], &status, 0) == -1)
		error_type();
	handle_exit(status);
}
