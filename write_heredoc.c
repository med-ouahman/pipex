/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 12:01:43 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/06 11:11:26 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	write_heredoc(t_pipex *pipex)
{
	int		fd;
	char	*line;
	size_t	len;

	fd = open(".here_doc", O_CREAT | O_WRONLY, 0777);
	if (fd < 0)
		return (clean(*pipex, 1), error(FILE_ERROR, "file error"));
	ft_printf("pipe heredoc>");
	line = get_next_line(0);
	if (!line)
		return (clean(*pipex, 1), error(MEMORY_ERROR, "memory error"));
	len = ft_strlen(line);
	while (!ft_strncmp(line, "\n", 1)
		|| ft_strncmp(line, pipex->limiter, len - 1))
	{
		write(fd, line, len);
		ft_printf("pipe heredoc>");
		free(line);
		line = get_next_line(0);
		if (!line)
			return (clean(*pipex, 1), error(MEMORY_ERROR, "memory error"));
		len = ft_strlen(line);
	}
	close(fd);
	return (0);
}
