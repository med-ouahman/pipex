/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:36:19 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/22 04:53:11 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	open_files(t_pipex *pipex, int n)
{
	if (n == 0)
	{
		if (!access(pipex->infile, F_OK) && access(pipex->infile, R_OK))
		{
			ft_printf_fd(2, "Permission denied: %s\n", pipex->infile);
			return (1);
		}
		pipex->fd1 = open(pipex->infile, O_RDONLY);
		if (pipex->fd1 < 0)
			ft_printf_fd(2, "no such file or directory: %s\n", pipex->infile);
		return (0);
	}
	if (!access(pipex->outfile, F_OK) && access(pipex->outfile, W_OK))
	{
		ft_printf_fd(2, "permission denied: %s\n", pipex->outfile);
		return (1);
	}
	pipex->fd2 = open(pipex->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->fd2 < 0)
	{
		ft_printf_fd(2, "no such file or directory: %s\n", pipex->outfile);
		return (1);
	}
	return (0);
}

int	**create_pipes(int count)
{
	int	**pipes;
	int	i;

	pipes = malloc(count * sizeof(int *));
	if (!pipes)
		return (NULL);
	i = 0;
	while (i < count)
	{
		pipes[i] = malloc(2 * sizeof(int));
		if (!pipes[i])
		{
			clear((void *)pipes);
			return (NULL);
		}
		if (pipe(pipes[i]) < 0)
		{
			close_pipes(pipes, i);
			clear((void *)pipes);
			return (NULL);
		}
		i++;
	}
	return (pipes);
}

int	manage_pipes(int i, t_pipex *pipex)
{
	int	err;

	err = 0;
	if (i == 0)
	{
		if (open_files(pipex, 0) == 1)
			return (1);
		if (pipex->fd1 < 0 || dup2(pipex->fd1, 0) == -1)
			err = 1;
	}
	if (i > 0)
		if (dup2(pipex->pipes[i - 1][0], 0) == -1)
			err = 1;
	if (i < pipex->count - 1)
		if (dup2(pipex->pipes[i][1], 1) == -1)
			err = 1;
	if (i == pipex->count - 1)
	{
		if (open_files(pipex, 1) == 1)
			return (1);
		if (pipex->fd2 < 0 || dup2(pipex->fd2, 1) == -1)
			err = 1;
	}
	return (err);
}

void	close_pipes(int	**pipes, int count)
{
	int	var;

	var = 0;
	while (var < count)
	{
		close_f(&pipes[var][0]);
		close_f(&pipes[var][1]);
		var++;
	}
}
