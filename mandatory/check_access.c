/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:02:54 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/21 05:31:00 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*get_cmdpath(int i, char **pvs, char *cmd)
{
	char	*cmdpath;
	size_t	size;

	if (i == -1)
		return (ft_strdup(cmd));
	size = ft_strlen(pvs[i]) + ft_strlen(cmd) + 2;
	cmdpath = malloc(size * sizeof(char));
	if (!cmdpath)
		return (NULL);
	cmdpath[0] = '\0';
	ft_strlcat(cmdpath, pvs[i], size);
	ft_strlcat(cmdpath, "/", size);
	ft_strlcat(cmdpath, cmd, size);
	return (cmdpath);
}

int	check_access(t_pipex *pipex, char *cmd)
{
	char	**pvs;
	int		i;

	pvs = ft_split(pipex->path + 5, ':');
	if (!pvs)
		return (1);
	i = -1;
	while (i == -1 || pvs[i])
	{
		pipex->cmdpath = get_cmdpath(i, pvs, cmd);
		if (!pipex->cmdpath)
			return (clear((void **)pvs), 1);
		if (!access(pipex->cmdpath, F_OK))
		{
			if (!access(pipex->cmdpath, X_OK))
				return (clear((void **)pvs), 0);
			free(pipex->cmdpath);
			clear((void **)pvs);
			return (errno);
		}
		free(pipex->cmdpath);
		i++;
	}
	return (clear((void **)pvs), errno);
}
