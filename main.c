/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/26 15:15:50 by arolland          #+#    #+#             */
/*   Updated: 2021/09/27 17:40:46 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_data	data[1];

	data->flag = 0;
	if (envp == NULL)
		return (1);
	if (ac != 5)
	{
		ft_putstr_fd("Error\nUsage : ./pipex infile cmd1 cmd2 outfile\n", 2);
		return (2);
	}
	exec_mandatory(data, av, envp);
	return (0);
}
