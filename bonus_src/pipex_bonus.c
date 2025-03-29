/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:25:23 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/22 07:50:57 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	open_files(t_pipex *pipex, char *infile, char *outfile)
{
	pipex->infile = infile;
	pipex->outfile = outfile;
}

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (av[1] && !ft_strcmp(av[1], "here_doc"))
		return (here_doc(ac, av, envp));
	if (ac < 5)
	{
		ft_printf_fd(1, "Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile\n");
		return (0);
	}
	pipex.heredoc = NULL;
	pipex.cmds = av + 2;
	pipex.count = ac - 3;
	pipex.envp = envp;
	pipex.path = extract_path(pipex.envp);
	if (!pipex.path)
		return (error(EXIT_FAILURE, "path not found\n"), 1);
	open_files(&pipex, av[1], av[ac - 1]);
	pipex.pids = malloc(pipex.count * sizeof(pid_t));
	if (!pipex.pids)
		return (error_type(), 1);
	pipex.pipes = create_pipes(pipex.count - 1);
	if (!pipex.pipes)
		return (free(pipex.pids), error_type(), 1);
	execute(&pipex);
	return (0);
}
