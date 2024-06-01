/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 10:41:01 by eismail           #+#    #+#             */
/*   Updated: 2024/06/01 13:07:10 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

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

void	ft_herdox(char **av, int *ac, int *herdox_pip)
{
	int		i;
	char	*temp;
	char	*str;

	i = 0;
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		temp = ft_strdup("");
		str = ft_strjoin(av[2], "\n");
		while ((ft_strncmp(temp, str, ft_strlen(str)) != 0) && (i++ >= 0))
		{
			free(temp);
			ft_putstr_fd(temp, herdox_pip[1]);
			ft_putstr_fd("pipe heredoc> ", 1);
			temp = get_next_line(0);
		}
		(*ac) -= 4;
		free(str);
		free(temp);
	}
	else
		(*ac) -= 3;
	close(herdox_pip[1]);
}

int	main(int ac, char **av, char **envp)
{
	int	*fds;
	int	**fd;
	int	*pid;
	int	i;
	int	herdox_pip[2];

	i = 0;
	if (ac < 5)
		ft_error("Too few arguments\n", 0);
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		if (pipe(herdox_pip) == -1)
			ft_error(NULL, 1);
	}
	ft_herdox(av, &ac, herdox_pip);
	fds = ft_open(av, herdox_pip[0], ac + 2);
	fd = ft_pip(ac);
	if (ft_strncmp(av[1], "here_doc", 9) == 0)
		pid = ft_pipex(&av[1], envp, fd, fds);
	else
		pid = ft_pipex(av, envp, fd, fds);
	ft_clean(ac, fd, fds, pid);
	return (0);
}
