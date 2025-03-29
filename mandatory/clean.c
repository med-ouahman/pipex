/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:38:19 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/22 00:19:48 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_f(int *fd)
{
	if (*fd < 0)
		return ;
	close(*fd);
	*fd = -1;
}

void	clean(t_pipex *pipex)
{
	if (pipex->fds[0] > -1)
	{
		close(pipex->fds[0]);
		pipex->fds[0] = -1;
	}
	if (pipex->fds[1] > -1)
	{
		close(pipex->fds[1]);
		pipex->fds[1] = -1;
	}
	if (pipex->fd1 >= 0)
	{
		close(pipex->fd1);
		pipex->fd1 = -1;
	}
	if (pipex->fd2 >= 0)
	{
		close(pipex->fd2);
		pipex->fd2 = -1;
	}
}
