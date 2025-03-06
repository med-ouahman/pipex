/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 10:25:27 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/06 11:45:29 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <time.h>
# include <sys/wait.h>

# define FDS 2

typedef enum e_error
{
	MEMORY_ERROR = 2,
	FORK_ERROR,
	PIPE_ERROR,
	FILE_ERROR,
	EXECVE_ERROR,
	PATH_ERROR
}	t_errors;

typedef struct s_pipex
{
	pid_t	pid;
	int		fd1;
	int		fd2;
	int		heredoc;
	t_list	*cmds;
	int		fds[FDS];
	char	**envp;
	char	*path;
	char	*limiter;
}	t_pipex;

t_list	*get_cmds(int ac, char **av);
int		add_command(t_list **cmds, char *command);
int		execute(t_pipex *pipex);
char	*extract_path(char **env);
char	*check_access(char *path, char *cmd);
int		clear(void **ptr);
int		here_doc(int ac, char **av, char **envp);
pid_t	child(char *cmd, t_pipex *pipex);
int		exec_cmd(char *cmd, t_pipex *pipex);
int		write_heredoc(t_pipex *pipex);
int		exec(t_pipex *pipex);
void	clean(t_pipex pipex, int n);
int		error(int code, char *message);

#endif
