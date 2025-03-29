/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/14 07:46:25 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/22 08:19:53 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static	void	clear_parent(t_pipex *pipex)
{
	if (pipex->heredoc)
		return ;
	free(pipex->pids);
	close_pipes(pipex->pipes, pipex->count - 1);
	clear2((void *)pipex->pipes, pipex->count - 1);
}

static void	wait_children(t_pipex *pipex)
{
	int	status;
	int	i;

	i = 0;
	while (i < pipex->count)
	{
		if (waitpid(pipex->pids[i], &status, 0) == -1)
		{
			i = -1;
			break ;
		}
		i++;
	}
	free(pipex->pids);
	if (i == -1)
		error_type();
	handle_exit(status);
}

void	exec_cmd(char *cmd, t_pipex *pipex)
{
	char	**argv;
	int		c;

	argv = ft_split(cmd, ' ');
	if (!argv)
		return (clear_parent(pipex), error(EXIT_FAILURE, "memory error\n"));
	if (!*argv)
	{
		clear((void *)argv);
		clear_parent(pipex);
		error(127, "command not found\n");
	}
	c = check_access(pipex, argv[0]);
	if (c != 0)
	{
		clear((void *)argv);
		clear_parent(pipex);
		if (c == 1)
			error(EXIT_FAILURE, "memory error\n");
		error_type();
	}
	execve(pipex->cmdpath, argv, pipex->envp);
	free(pipex->cmdpath);
	clear((void *)argv);
	return (clear_parent(pipex), error(EXIT_FAILURE, "execve failed\n"));
}

static pid_t	child(int i, char *cmd, t_pipex *pipex)
{
	int	pip;

	pipex->pids[i] = fork();
	if (pipex->pids[i] < 0)
		return (-1);
	if (pipex->pids[i] == 0)
	{
		pip = manage_pipes(i, pipex);
		clean(pipex);
		close_pipes(pipex->pipes, pipex->count - 1);
		if (pip == 1)
		{
			clear_parent(pipex);
			exit(EXIT_FAILURE);
		}
		exec_cmd(cmd, pipex);
	}
	return (pipex->pids[i]);
}

void	execute(t_pipex *pipex)
{
	int	i;

	i = 0;
	pipex->fd1 = -1;
	pipex->fd2 = -1;
	while (i < pipex->count)
	{
		if (child(i, pipex->cmds[i], pipex) == -1)
		{
			free(pipex->pids);
			close_pipes(pipex->pipes, pipex->count - 1);
			clear2((void *)pipex->pipes, pipex->count - 1);
			error_type();
		}
		i++;
	}
	close_pipes(pipex->pipes, pipex->count - 1);
	clear2((void *)pipex->pipes, pipex->count - 1);
	wait_children(pipex);
}
