/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 14:57:58 by arolland          #+#    #+#             */
/*   Updated: 2021/09/18 14:59:07 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_arr(char **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
	}
}

void	free_tab(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	str = NULL;
}

void	free_all(t_data *data)
{
	int	i;

	i = -1;
	if (data->cmd)
		free_tab(data->cmd);
	if (data->pids)
		free(data->pids);
	if (data->pipes)
	{
		while (++i < data->size + 1)
			free(data->pipes[i]);
		free(data->pipes);
	}
	exit(EXIT_FAILURE);
}

void	free_mandatory(t_data *data, char **cmd, char *str)
{
	int	i;

	i = -1;
	if (data->pipes_mandatory)
	{
		while (++i < 2 + 1)
			free(data->pipes_mandatory[i]);
		free(data->pipes_mandatory);
	}
	if (str)
	{
		free_arr(&str);
	}
	if (cmd)
	{
		free_tab(cmd);
	}
	exit(EXIT_FAILURE);
}
