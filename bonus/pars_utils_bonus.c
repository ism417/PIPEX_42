/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 20:27:28 by eismail           #+#    #+#             */
/*   Updated: 2024/06/01 13:28:29 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	**ft_get_arg(char *s, char **arg)
{
	char	**str3;
	char	**str2;
	char	*s2;
	char	*s1;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] && (s[i] != '\'' && s[i] != '"'))
		i++;
	if (s[i] == '\'' || s[i] == '"')
		i--;
	s1 = ft_substr(s, 0, i + 1);
	s2 = ft_substr(s, ++i, ft_strlen(s));
	str2 = ft_split(s1, ' ');
	if (s[i] == '\'')
		str3 = ft_split(s2, '\'');
	else
		str3 = ft_split(s2, '"');
	arg = ft_join(str2, str3);
	return (free(s1), free(s2), arg);
}

char	*ft_get_cmd(char *s)
{
	char	**str;
	char	*cmd;

	str = ft_split(s, ' ');
	if (!str || str[0] == '\0')
		return (NULL);
	if (access(str[0], X_OK) != -1)
	{
		cmd = ft_strdup(str[0]);
		return (free_split(str), cmd);
	}
	cmd = ft_strjoin("/", str[0]);
	free_split(str);
	return (cmd);
}

char	*ft_path(char **env, char *s)
{
	int		i;
	char	**paths;
	char	*cmd;
	char	*str;

	i = 0;
	cmd = ft_get_cmd(s);
	if (access(cmd, X_OK) != -1)
		return (cmd);
	while (env[i] && (ft_strncmp(env[i], "PATH", 4) != 0))
		i++;
	if (!env[i])
		ft_error("command not found", 0);
	paths = ft_split(&env[i][5], ':');
	i = 0;
	while (paths[i])
	{
		str = ft_strjoin(paths[i], cmd);
		if (access(str, X_OK) != -1)
			return (free_split(paths), free(cmd), str);
		i++;
		free(str);
	}
	return (free_split(paths), free(cmd), NULL);
}

t_cmd	*ft_set(char **env, char *s)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		ft_error(NULL, 1);
	cmd->path = ft_path(env, s);
	if (!cmd->path)
	{
		ft_error("pipex : command not found\n", 0);
		return (free(cmd), NULL);
	}
	if (ft_strncmp(&s[ft_strlen(s) - 3], ".sh", 3) == 0)
		return (ft_bash(s, cmd));
	cmd->args = ft_get_arg(s, cmd->args);
	if (!cmd->args)
	{
		ft_error("pipex : command not found\n", 0);
		return (free(cmd->path), free(cmd), NULL);
	}
	return (cmd);
}

void	free_cmd(t_cmd *cmd)
{
	free_split(cmd->args);
	free(cmd->path);
	free(cmd);
}
