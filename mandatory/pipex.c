/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:25:23 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/22 06:50:08 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (ac != 5)
	{
		ft_printf_fd(1, "Usage: ./pipex infile cmd1 cmd2 outfile\n");
		return (EXIT_SUCCESS);
	}
	pipex.cmds = av + 2;
	pipex.envp = envp;
	pipex.infile = av[1];
	pipex.outfile = av[ac - 1];
	pipex.fd1 = -1;
	pipex.fd2 = -1;
	pipex.fds[0] = -1;
	pipex.fds[1] = -1;
	pipex.path = extract_path(pipex.envp);
	if (!pipex.path)
		return (error(EXIT_FAILURE, "path not found\n"), 1);
	execute(&pipex);
	return (0);
}
