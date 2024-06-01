/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 10:41:01 by eismail           #+#    #+#             */
/*   Updated: 2024/06/01 12:55:21 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *s, int error)
{
	if (error == 1)
		perror("pipex :");
	else
		ft_putstr_fd(s, 2);
	exit(1);
}

void	free_int(int **p, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		free(p[i]);
		i++;
	}
	free(p);
}

int	main(int ac, char **av, char **envp)
{
	int	*fds;
	int	*pid;
	int	**fd;
	int	i;

	i = 0;
	if (ac != 5)
		ft_error("Arguments error\n", 0);
	ac -= 3;
	fds = ft_open(av, ac + 2);
	fd = ft_pip(ac);
	pid = ft_pipex(av, envp, fd, fds);
	ft_clean(ac, fd, fds, pid);
	return (0);
}
