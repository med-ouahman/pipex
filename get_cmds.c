/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 09:48:46 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/05 15:22:02 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_list	*get_cmds(int ac, char **av)
{
	t_list	*cmds;
	int		i;

	cmds = NULL;
	i = 0;
	while (i < ac)
	{
		if (add_command(&cmds, av[i]) == 1)
			return (ft_lstclear(&cmds, free), NULL);
		i++;
	}
	return (cmds);
}
