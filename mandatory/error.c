/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 06:59:40 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/17 03:46:00 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error(int code, char *message)
{
	if (message)
		ft_putstr_fd(message, 2);
	exit(code);
}

void	error_type(void)
{
	if (errno == ENOENT)
		return (ft_putstr_fd("command not found\n", 2), exit(127));
	if (errno == EACCES)
		return (ft_putstr_fd("permission denied\n", 2), exit(126));
	if (errno == ENOMEM)
		return (ft_putstr_fd("memory error\n", 2), exit(1));
}

void	handle_exit(int status)
{
	if (WIFEXITED(status))
		exit(WEXITSTATUS(status));
	if (WIFSIGNALED(status))
		exit(WTERMSIG(status) + 128);
}
