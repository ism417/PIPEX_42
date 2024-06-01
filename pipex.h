/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 10:41:17 by eismail           #+#    #+#             */
/*   Updated: 2024/06/01 16:00:36 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>

typedef struct t_data
{
	char	*path;
	char	**args;
}			t_cmd;
int		*ft_pipex(char **av, char **envp, int **fd, int *fds);
void	free_split(char **split_str);
char	**ft_get_arg(char *s, char **arg);
char	*ft_get_cmd(char *s);
void	ft_error(char *s, int error);
char	*ft_path(char **env, char *s);
t_cmd	*ft_set(char **env, char *s);
int		*ft_open(char **s, int i);
int		**ft_pip(int ac);
void	ft_close(int ac, int **pipes, int *fds);
void	ft_stdin(int **pipes, int pid, int *fds);
void	ft_stdout(int ac, int **pipes, int pid, int *fds);
void	ft_clean(int ac, int **pipes, int *fds, int *pid);
void	free_cmd(t_cmd *cmd);
void	fd_hindler(int ac, int **fd, int i, int *fds);
int		cmd_count(char **av);
t_cmd	*ft_bash(char *s, t_cmd *cmd);
int		ft_allspace(char *s);
int		ft_arg_count(char **s1, char **s2);
char	**ft_cpy(char **s, char **new, int *n);
char	**ft_join(char **s1, char **s2);
void	free_int(int **p, int n);
#endif
