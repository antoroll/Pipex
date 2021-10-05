/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 14:59:00 by arolland          #+#    #+#             */
/*   Updated: 2021/09/17 17:30:27 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_path(t_data *data, char **paths, char *cmd)
{
	int		i;
	char	*final_path;
	char	*half_path;

	i = 0;
	if (cmd == NULL)
	{
		data->flag2 = 1;
		return (NULL);
	}
	while (paths[i])
	{
		half_path = ft_strjoin(paths[i], "/");
		final_path = ft_strjoin(half_path, cmd);
		free_arr(&half_path);
		if (access(final_path, F_OK) == 0)
			return (final_path);
		free_arr(&final_path);
		i++;
	}
	if (access(cmd, F_OK) == 0)
		return (cmd);
	return (NULL);
}

char	**split_path(char *path, char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], path, ft_strlen(path)) == 0)
			paths = ft_split(&envp[i][5], ':');
		i++;
	}
	return (paths);
}

char	*path(t_data *data, char **envp, char **cmd)
{
	char	**paths;
	char	*path;

	paths = split_path("PATH=", envp);
	path = get_path(data, paths, *cmd);
	free_tab(paths);
	return (path);
}
