/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/03 14:58:19 by arolland          #+#    #+#             */
/*   Updated: 2021/09/27 14:41:19 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_exit(t_data *data, char *str, int file, char *tab)
{
	if (ft_strncmp(str, "infile", 6) == 0)
	{
		if (file == -1)
		{
			ft_putstr_fd("Invalid infile\n", 2);
			free_mandatory(data, NULL, tab);
			exit(EXIT_FAILURE);
		}
	}
	if (ft_strncmp(str, "outfile", 7) == 0)
	{
		if (file == -1)
		{
			ft_putstr_fd("Invalid outfile.\n", 2);
			free_mandatory(data, NULL, tab);
			exit(EXIT_FAILURE);
		}
	}
}

void	ft_exit_bonus(t_data *data, char *str, int file)
{
	if (ft_strncmp(str, "infile", 6) == 0)
	{
		if (file == -1)
		{
			ft_putstr_fd("Invalid infile.\n", 2);
			free_all(data);
			exit(EXIT_FAILURE);
		}
	}
	if (ft_strncmp(str, "outfile", 7) == 0)
	{
		if (file == -1)
		{
			ft_putstr_fd("Invalid outfile\n", 2);
			free_all(data);
			exit(EXIT_FAILURE);
		}
	}
}

void	invalid_command(t_data *data, char **cmd)
{
	if (*cmd == NULL)
	{
		if (cmd)
		{
			ft_putstr_fd("Command not found : « »\n", 2);
			free_mandatory(data, cmd, NULL);
		}
		exit(EXIT_FAILURE);
	}
}

void	invalid_command_bonus(t_data *data)
{
	if (*data->cmd == NULL)
	{
		if (data->cmd)
		{
			ft_putstr_fd("Command not found : « »\n", 2);
			free_all(data);
		}
		exit(EXIT_FAILURE);
	}
}

void	error_args(t_data *data)
{	
	ft_putstr_fd("Error\nUsage1 : ./pipex here_doc"
		" LIMITER cmd1 cmd2 outfile\n", 2);
	ft_putstr_fd("Usage2 : ./pipex infile cmd1 "
		"cmd2... cmd n outfile\nInfile must have READ rights\n", 2);
	free_all(data);
	exit(EXIT_FAILURE);
}
