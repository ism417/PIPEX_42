/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 20:30:50 by eismail           #+#    #+#             */
/*   Updated: 2024/06/01 12:57:44 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_clean(int ac, int **pipes, int *fds, int *pid)
{
	int	i;

	i = 0;
	ft_close(ac, pipes, fds);
	free_int(pipes, ac);
	while (i < ac)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	free(pid);
	free(fds);
}

void	ft_close(int ac, int **pipes, int *fds)
{
	int	i;

	i = 0;
	while (i < ac - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		i++;
	}
	close(fds[0]);
	close(fds[1]);
}

void	ft_stdin(int **pipes, int pid, int *fds)
{
	if (pid == 0)
		dup2(fds[0], STDIN_FILENO);
	if (pid != 0)
		dup2(pipes[pid - 1][0], STDIN_FILENO);
}

void	ft_stdout(int ac, int **pipes, int pid, int *fds)
{
	if (pid == ac - 1)
		dup2(fds[1], STDOUT_FILENO);
	if (pid != ac - 1)
		dup2(pipes[pid][1], STDOUT_FILENO);
}

int	cmd_count(char **av)
{
	int	ac;

	ac = 0;
	while (av[ac])
		ac++;
	ac -= 3;
	return (ac);
}
