/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 17:10:48 by eismail           #+#    #+#             */
/*   Updated: 2024/06/01 13:10:38 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

t_cmd	*ft_bash(char *s, t_cmd *cmd)
{
	char	*bash;
	char	*str;

	free(cmd->path);
	cmd->path = ft_strdup("/bin/bash");
	if (!cmd->path)
	{
		ft_error("pipex : command not found\n", 0);
		return (free(cmd), NULL);
	}
	bash = ft_strdup("bash ");
	str = ft_strjoin(bash, s);
	cmd->args = ft_get_arg(str, cmd->args);
	free(bash);
	free(str);
	if (!cmd->args)
	{
		ft_error("pipex : command not found\n", 0);
		return (free(cmd->path), free(cmd), NULL);
	}
	return (cmd);
}

int	*ft_pipex(char **av, char **envp, int **fd, int *fds)
{
	t_cmd	*cmd;
	int		i;
	int		ac;
	int		*pids;

	i = -1;
	ac = cmd_count(av);
	pids = malloc(sizeof(int) * ac);
	if (!pids)
		ft_error(NULL, 1);
	while (++i < ac)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			ft_error(NULL, 1);
		if (pids[i] == 0)
		{
			cmd = ft_set(envp, av[i + 2]);
			fd_hindler(ac, fd, i, fds);
			if (execve(cmd->path, cmd->args, envp) == -1)
				return (free(pids), free_split(cmd->args), free(cmd->path),
					free(cmd), ft_error(NULL, 1), NULL);
		}
	}
	return (pids);
}

int	**ft_pip(int ac)
{
	int	i;
	int	**fd;

	i = 0;
	fd = malloc(sizeof(int *) * ac);
	if (!fd)
		ft_error(NULL, 1);
	while (i < ac)
	{
		fd[i] = malloc(sizeof(int) * 2);
		if (!fd[i++])
		{
			free_int(fd, i);
			ft_error(NULL, 1);
		}
	}
	i = 0;
	while ((i < ac - 1))
	{
		if (pipe(fd[i]) == -1)
			ft_error(NULL, 1);
		i++;
	}
	return (fd);
}

int	*ft_open(char **s, int pipe, int i)
{
	int	*fds;

	fds = malloc(sizeof(int) * 2);
	if (!fds)
		ft_error(NULL, 1);
	if (ft_strncmp(s[1], "here_doc", 9) == 0)
	{
		fds[0] = pipe;
		fds[1] = open(s[i + 1], O_CREAT | O_RDWR | O_APPEND, 0644);
		if (fds[1] < 0)
			ft_error(NULL, 1);
	}
	else 
	{
		fds[0] = open(s[1], O_RDONLY);
		fds[1] = open(s[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
		if (fds[1] < 0)
		{
			free(fds);
			ft_error(NULL, 1);
		}
	}
	return (fds);
}

void	fd_hindler(int ac, int **fd, int i, int *fds)
{
	if (fds[0] == -1 && i == 0)
		return(free_int(fd, ac), free(fds), ft_error(NULL, 1));
	ft_stdin(fd, i, fds);
	ft_stdout(ac, fd, i, fds);
	ft_close(ac, fd, fds);
}
