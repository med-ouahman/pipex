/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 10:24:20 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/05 15:22:09 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*extract_path(char **envp)
{
	char	**ptr;

	ptr = envp;
	while (*ptr)
	{
		if (!ft_strncmp(*ptr, "PATH", 4))
			return (*ptr);
		ptr++;
	}
	return (NULL);
}
