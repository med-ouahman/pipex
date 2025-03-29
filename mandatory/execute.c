/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:53:16 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/22 08:35:57 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	open_files(int i, t_pipex *pipex)
{
	if (i == 0)
	{
		if (!access(pipex->infile, F_OK) && access(pipex->infile, R_OK))
		{
			ft_printf_fd(2, "permission denied: %s\n", pipex->infile);
			return (1);
		}
		pipex->fd1 = open(pipex->infile, O_RDONLY);
		if (pipex->fd1 < 0)
		{
			ft_printf_fd(2, "no such file or directory: %s\n", pipex->infile);
			return (1);
		}
		return (0);
	}
	if (!access(pipex->outfile, F_OK) && access(pipex->outfile, W_OK))
		return (ft_printf_fd(2, "permission denied: %s\n", pipex->outfile), 1);
	pipex->fd2 = open(pipex->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->fd2 < 0)
	{
		ft_printf_fd(2, "no such file or directory: %s\n", pipex->outfile);
		return (1);
	}
	return (0);
}

static void	handle_pipes(int i, t_pipex *pipex)
{
	if (i == 0)
	{
		if (pipex->fd1 < 0 || dup2(pipex->fd1, 0) == -1)
			return (clean(pipex), error_type());
		close_f(&pipex->fds[0]);
		if (dup2(pipex->fds[1], 1) == -1)
			return (clean(pipex), exit(1));
		close_f(&pipex->fd1);
		close_f(&pipex->fds[1]);
	}
	else
	{
		if (pipex->fd2 < 0 || dup2(pipex->fd2, 1) == -1)
			return (clean(pipex), error_type());
		close_f(&pipex->fds[1]);
		if (dup2(pipex->fds[0], 0) == -1)
			return (clean(pipex), exit(1));
		close_f(&pipex->fd2);
		close_f(&pipex->fds[0]);
	}
}

static void	exec_cmd(char *cmd, t_pipex *pipex)
{
	char	**argv;
	int		c;

	argv = ft_split(cmd, ' ');
	if (!argv)
		error(EXIT_FAILURE, "memory error\n");
	if (!*argv)
	{
		clear((void *)argv);
		error(127, "command not found\n");
	}
	c = check_access(pipex, argv[0]);
	if (c != 0)
	{
		clear((void *)argv);
		if (c == 1)
			error(EXIT_FAILURE, "memory error\n");
		error_type();
	}
	execve(pipex->cmdpath, argv, pipex->envp);
	free(pipex->cmdpath);
	clear((void *)argv);
	return (error(EXIT_FAILURE, "execve failed\n"));
}

static pid_t	child(int i, char *cmd, t_pipex *pipex)
{
	pipex->pid = fork();
	if (pipex->pid < 0)
		return (clean(pipex), error(EXIT_FAILURE, "fork error\n"), -1);
	if (pipex->pid == 0)
	{
		if (open_files(i, pipex) == 1)
		{
			clean(pipex);
			error(EXIT_FAILURE, NULL);
		}
		else
		{
			handle_pipes(i, pipex);
			clean(pipex);
			exec_cmd(cmd, pipex);
		}
	}
	return (pipex->pid);
}

void	execute(t_pipex *pipex)
{
	int		status;

	if (pipe(pipex->fds) < 0)
		return (clean(pipex), error(EXIT_FAILURE, "pipe error\n"));
	child(0, pipex->cmds[0], pipex);
	pipex->pid2 = pipex->pid;
	child(1, pipex->cmds[1], pipex);
	clean(pipex);
	if (waitpid(pipex->pid2, NULL, 0) == -1)
		error(EXIT_FAILURE, "waitpid error\n");
	if (waitpid(pipex->pid, &status, 0) == -1)
		error(EXIT_FAILURE, "waitpid error\n");
	handle_exit(status);
}
