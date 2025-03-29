/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/01 09:03:09 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/22 06:16:55 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	here_doc(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 6)
	{
		ft_printf_fd(1, "Usage: ./pipex here_doc LIMITER cmd1 cmd2 file\n");
		return (0);
	}
	pipex.heredoc = ".here_doc";
	pipex.cmds = av + 3;
	pipex.count = 2;
	pipex.limiter = av[2];
	pipex.envp = envp;
	pipex.outfile = av[ac - 1];
	pipex.path = extract_path(envp);
	if (!pipex.path)
		return (error(ERROR, "path not found\n"), 1);
	execute_heredoc(&pipex);
	return (0);
}
