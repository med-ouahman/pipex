/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 21:00:53 by mouahman          #+#    #+#             */
/*   Updated: 2025/02/06 09:52:36 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	add_command(t_list **cmds, char *command)
{
	t_list	*new;
	void	*content;

	content = ft_strdup(command);
	if (!content)
		return (ft_lstclear(cmds, free), 1);
	new = ft_lstnew(content);
	if (!new)
		return (ft_lstclear(cmds, free), free(content), 1);
	ft_lstadd_back(cmds, new);
	return (0);
}
