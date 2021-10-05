/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arolland <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:00:40 by arolland          #+#    #+#             */
/*   Updated: 2021/09/28 13:50:52 by arolland         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	here_doc_parse(t_data *data, char **argv)
{
	char	*line;

	line = NULL;
	data->heredoc = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (!data->heredoc)
	{
		free_all(data);
		exit(EXIT_FAILURE);
	}
	write(STDOUT_FILENO, "pipe heredoc> ", 14);
	while (get_next_line(0, &line, 1) != 0)
	{
		if (ft_strncmp(line, argv[2], ft_strlen(argv[2])) == 0)
		{
			free(line);
			close(data->heredoc);
			break ;
		}
		write(STDOUT_FILENO, "pipe heredoc> ", 14);
		write(data->heredoc, line, ft_strlen(line));
		write(data->heredoc, "\n", 1);
		free(line);
	}
}

void	here_doc_child(t_data *data, int *end, char **argv, char **envp)
{
	char	**cmd1;
	char	*paths;

	cmd1 = NULL;
	data->heredoc = open("heredoc", O_RDONLY, 0644);
	dup2(data->heredoc, STDIN_FILENO);
	close(end[0]);
	dup2(end[1], STDOUT_FILENO);
	cmd1 = ft_split(argv[3], ' ');
	free_cmd(data, cmd1);
	paths = path(data, envp, cmd1);
	if (paths == NULL)
		free_paths(data, paths, cmd1);
	if (execve(paths, cmd1, envp) == -1)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(cmd1[0], 2);
		free_tab(cmd1);
		exit(EXIT_FAILURE);
	}
}

void	here_doc_parent(t_data *data, int *end, char **argv, char **envp)
{
	char	**cmd;
	char	*paths;

	cmd = NULL;
	data->outfile = open(argv[5], O_RDWR | O_CREAT | O_APPEND, 0644);
	ft_exit_bonus(data, "outfile", data->outfile);
	waitpid(data->pid, 0, 0);
	unlink("heredoc");
	close(end[1]);
	dup2(end[0], STDIN_FILENO);
	close(end[0]);
	dup2(data->outfile, STDOUT_FILENO);
	close(data->outfile);
	cmd = ft_split(argv[4], ' ');
	free_cmd(data, cmd);
	paths = path(data, envp, cmd);
	if (paths == NULL)
		free_paths(data, paths, cmd);
	if (execve(paths, cmd, envp) == -1)
	{
		ft_putstr_fd("Command not found: ", 2);
		ft_putendl_fd(cmd[0], 2);
		free_tab(cmd);
		exit(EXIT_FAILURE);
	}
}

void	exec_heredoc_bonus(t_data *data, char **argv, char **env)
{
	int	end[2];

	pipe(end);
	here_doc_parse(data, argv);
	data->pid = fork();
	if (data->pid < 0)
		ft_putstr_fd("Error\nFork failed\n", 2);
	else if (data->pid == 0)
		here_doc_child(data, end, argv, env);
	else if (data->pid > 0)
		here_doc_parent(data, end, argv, env);
}
