/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_heredoc_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:01:43 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/22 06:17:00 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static int	write_to_file(int fd, char *line, char *limiter)
{
	size_t	len;

	len = ft_strlen(line);
	if (!ft_strncmp(line, limiter, len - 1) && ft_strcmp(line, "\n"))
		return (1);
	write(fd, line, len);
	return (0);
}

static void	pipe_heredoc(t_pipex *pipex)
{
	char	*line;
	size_t	len;

	ft_printf_fd(1, "pipe heredoc>");
	line = get_next_line(STDIN_FILENO);
	if (!line && errno == ENOMEM)
		return (clean(pipex), error_type());
	len = ft_strlen(line);
	while (errno != ENOMEM)
	{
		if (line)
		{
			if (write_to_file(pipex->fd1, line, pipex->limiter))
				break ;
			free(line);
			ft_printf_fd(1, "pipe heredoc>");
			line = get_next_line(STDIN_FILENO);
		}
		else if (!line && errno == ENOMEM)
			return (clean(pipex), error(1, "memory error\n"));
		else if (!line)
			line = get_next_line(STDIN_FILENO);
	}
	free(line);
}

void	write_heredoc(t_pipex *pipex)
{
	pipex->fd1 = open(pipex->heredoc, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (pipex->fd1 < 0)
		return (clean(pipex), error(ERROR, "file error\n"));
	pipe_heredoc(pipex);
	close(pipex->fd1);
}
