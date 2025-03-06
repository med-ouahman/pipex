/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_access.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 11:02:54 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/06 10:07:12 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*check_access(char *path, char *cmd)
{
	char	**pvs;
	char	*cmdpath;
	size_t	size;
	int		i;

	pvs = ft_split(path + 5, ':');
	if (!pvs)
		return (error(MEMORY_ERROR, NULL), NULL);
	i = 0;
	while (pvs[i])
	{
		size = ft_strlen(pvs[i]) + ft_strlen(cmd) + 2;
		cmdpath = malloc(size * sizeof(char) + 1);
		if (!cmdpath)
			return (clear((void *)pvs), error(MEMORY_ERROR, NULL), NULL);
		cmdpath[0] = '\0';
		ft_strlcat(cmdpath, pvs[i], size);
		ft_strlcat(cmdpath, "/", size);
		ft_strlcat(cmdpath, cmd, size);
		if (access(cmdpath, F_OK | X_OK) == 0)
			return (clear((void *)pvs), cmdpath);
		free(cmdpath);
		i++;
	}
	return (clear((void *)pvs), NULL);
}
