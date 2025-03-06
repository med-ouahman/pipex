/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:25:23 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/06 10:58:41 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	pipex;

	if (av && av[1] && !ft_strncmp(av[1], "here_doc", ft_strlen(av[1])))
		return (here_doc(ac, av, envp));
	if (ac < 5)
	{
		ft_printf("Usage: ./pipex infile cmd1 cmd2 ... cmdn outfile\n");
		return (0);
	}
	pipex.cmds = get_cmds(ac - 3, av + 2);
	if (!pipex.cmds)
		return (error(MEMORY_ERROR, "memory error"));
	pipex.envp = envp;
	pipex.fd1 = open(av[1], O_RDONLY, 0777);
	if (pipex.fd1 < 0)
		return (error(FILE_ERROR, "No such file or directory"));
	pipex.fd2 = open(av[ac - 1], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (pipex.fd2 < 0)
		return (error(FILE_ERROR, "file creation failed"));
	execute(&pipex);
	return (0);
}
