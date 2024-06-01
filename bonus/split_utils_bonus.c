/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eismail <eismail@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 20:24:32 by eismail           #+#    #+#             */
/*   Updated: 2024/05/31 19:20:27 by eismail          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_split(char **split_str)
{
	int	i;

	i = 0;
	while (split_str[i])
	{
		free(split_str[i]);
		i++;
	}
	free(split_str);
}

int	ft_allspace(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (1);
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	ft_arg_count(char **s1, char **s2)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (s1[i])
	{
		if (ft_allspace(s1[i]) == 1)
			j++;
		i++;
	}
	len = i - j;
	i = 0;
	j = 0;
	while (s2[j])
	{
		if (ft_allspace(s2[j]) == 1)
			i++;
		j++;
	}
	len += (j - i);
	return (len);
}

char	**ft_cpy(char **s, char **new, int *n)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (s[j])
	{
		if (ft_allspace(s[j]) != 1)
		{
			while (s[j][i] == ' ')
				i++;
			if (s[j][i] == '\'')
				new[*n] = ft_split(s[j], '\'')[1];
			else if (s[j][i] == '"')
				new[*n] = ft_split(s[j], '"')[1];
			else
				new[*n] = ft_strdup(s[j]);
			(*n)++;
		}
		j++;
	}
	return (new);
}

char	**ft_join(char **s1, char **s2)
{
	int		i;
	int		n;
	int		j;
	int		len;
	char	**new;

	i = 0;
	n = 0;
	j = 0;
	if (!s2)
		return (s1);
	len = ft_arg_count(s1, s2);
	new = malloc(sizeof(char *) * len + 1);
	while (s1[i])
	{
		if (ft_allspace(s2[j]) != 1)
		{
			new[n] = ft_strdup(s1[i]);
			n++;
		}
		i++;
	}
	new = ft_cpy(s2, new, &n);
	new[n] = NULL;
	return (new);
}