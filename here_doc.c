/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 09:03:09 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/06 11:25:06 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	here_doc(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac < 6)
		return (ft_printf("Usage: /pipex here_doc LIMITER cmd cmd1 file\n"), 0);
	pipex.cmds = get_cmds(ac - 4, av + 3);
	if (!pipex.cmds)
		return (clean(pipex, 1), error(MEMORY_ERROR, "memory error"));
	pipex.limiter = av[2];
	pipex.envp = envp;
	pipex.path = extract_path(envp);
	pipex.heredoc = open(av[ac - 1], O_CREAT | O_WRONLY | O_APPEND, 0777);
	if (pipex.heredoc < 0)
		return (clean(pipex, 1), error(FILE_ERROR, "file error"));
	write_heredoc(&pipex);
	pipex.fd1 = open(".here_doc", O_RDONLY, 0777);
	if (pipex.fd1 < 0)
		return (clean(pipex, 1), error(FILE_ERROR, "file error"));
	exec(&pipex);
	clean(pipex, 1);
	return (0);
}

int	exec(t_pipex *pipex)
{
	t_list	*ptr;
	int		status;

	ptr = pipex->cmds;
	dup2(pipex->fd1, 0);
	while (ptr->next)
	{
		if (pipe(pipex->fds) < 0)
			return (error(PIPE_ERROR, "pipe error"));
		child(ptr->content, pipex);
		ptr = ptr->next;
	}
	dup2(pipex->heredoc, 1);
	child(ptr->content, pipex);
	close(pipex->fd1);
	unlink(".here_doc");
	waitpid(pipex->pid, &status, 0);
	if (WIFEXITED(status))
	{
		clean(*pipex, 1);
		exit(WEXITSTATUS(status));
	}
	return (0);
}
