/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 19:38:19 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/03 19:43:42 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	clean(t_pipex pipex, int n)
{
	ft_lstclear(&pipex.cmds, free);
	if (n == 0)
	{
		close(pipex.fd1);
		close(pipex.fd2);
	}
	else if (n == 1)
		close(pipex.heredoc);
}
