/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mouahman <mouahman@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 00:47:49 by mouahman          #+#    #+#             */
/*   Updated: 2025/03/22 06:48:49 by mouahman         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include "../libft/libft.h"
# include <fcntl.h>
# include <string.h>
# include <time.h>
# include <sys/wait.h>
# include <errno.h>

# define ERROR 1

typedef struct s_pipex
{
	int		fd1;
	int		fd2;
	int		fds[2];
	int		count;
	char	*heredoc;
	int		**pipes;
	pid_t	*pids;
	char	**cmds;
	char	**envp;
	char	*path;
	char	*cmdpath;
	char	*infile;
	char	*outfile;
	char	*limiter;
}	t_pipex;

void	write_heredoc(t_pipex *pipex);
void	exec_cmd(char *cmd, t_pipex *pipex);
int		here_doc(int ac, char **av, char **envp);
void	clean(t_pipex *pipex);
void	close_f(int *fd);
void	error(int code, char *message);
void	error_type(void);
void	execute(t_pipex *pipex);
char	*extract_path(char **envp);
int		check_access(t_pipex *pipex, char *cmd);
void	clear(void **ptr);
void	clear2(void **ptr1, int count);
void	handle_exit(int status);
int		**create_pipes(int count);
void	close_pipes(int	**pipes, int count);
int		manage_pipes(int i, t_pipex *pipex);
void	execute_heredoc(t_pipex *pipex);

#endif
