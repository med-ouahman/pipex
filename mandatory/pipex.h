/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:25:27 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/22 06:48:56 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <time.h>
# include <sys/wait.h>

# define FDS 2
# define ERROR 1
# define FIVE 5

typedef struct s_pipex
{
	pid_t	pid;
	pid_t	pid2;
	int		fd1;
	int		fd2;
	char	*infile;
	char	*outfile;
	int		fds[FDS];
	char	**cmds;
	char	**envp;
	char	*path;
	char	*cmdpath;
}	t_pipex;

void	execute(t_pipex *pipex);
char	*extract_path(char **env);
int		check_access(t_pipex *pipex, char *cmd);
void	clear(void **ptr);
void	clear2(void **ptr1, void **ptr2);
void	clean(t_pipex *pipex);
void	close_f(int *fd);
void	error(int code, char *message);
void	error_type(void);
void	handle_exit(int status);

#endif
