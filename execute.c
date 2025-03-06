/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 10:53:16 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/06 10:35:30 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	execute(t_pipex *pipex)
{
	t_list	*ptr;
	int		status;

	ptr = pipex->cmds;
	dup2(pipex->fd1, 0);
	pipex->path = extract_path(pipex->envp);
	if (!pipex->path)
		return (error(PATH_ERROR, "path not found"));
	while (ptr->next)
	{
		if (pipe(pipex->fds) < 0)
			return (clean(*pipex, 0), error(PIPE_ERROR, "pipe error"));
		child(ptr->content, pipex);
		ptr = ptr->next;
	}
	dup2(pipex->fd2, 1);
	child(ptr->content, pipex);
	waitpid(pipex->pid, &status, 0);
	if (WIFEXITED(status))
	{
		clean(*pipex, 0);
		exit(WEXITSTATUS(status));
	}
	return (0);
}

pid_t	child(char *cmd, t_pipex *pipex)
{
	pipex->pid = fork();
	if (pipex->pid < 0)
		return (clean(*pipex, 0), error(FORK_ERROR, "fork error"));
	if (pipex->pid == 0)
	{
		close(pipex->fds[0]);
		dup2(pipex->fds[1], 1);
		if (exec_cmd(cmd, pipex) < 0)
			return (-1);
	}
	else
	{
		close(pipex->fds[1]);
		dup2(pipex->fds[0], 0);
	}
	return (pipex->pid);
}

int	exec_cmd(char *cmd, t_pipex *pipex)
{
	char	**argv;
	char	*cmdpath;

	argv = ft_split(cmd, ' ');
	if (!argv)
		return (error(MEMORY_ERROR, "memory error"));
	cmdpath = check_access(pipex->path, argv[0]);
	if (!cmdpath)
		return (clear((void *)argv), -1);
	execve(cmdpath, argv, pipex->envp);
	free(cmdpath);
	clear((void *)argv);
	error(EXECVE_ERROR, "execve failed");
	return (-1);
}
