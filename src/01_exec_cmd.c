/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 00:33:46 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/14 19:00:02 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static t_data	*init_data(t_cmd *cmd, int ac, char **av, char **ev)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit_error("Error: malloc failed\n", cmd, NULL);
	data->env = ev;
	data->infile = av[1];
	data->outfile = av[ac - 1];
	data->i = 0;
	return (data);
}

static void	exec_child(t_cmd *cmd, t_data *data, int i)
{
	int		fd;

	if (i == 0)
	{
		fd = open(data->infile, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	if (cmd[i + 1].cmd == NULL)
	{
		fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	if (i > 0)
		dup2(data->tmpfd, STDIN_FILENO);
	if (cmd[i + 1].cmd != NULL)
	{
		dup2(data->pipefd[1], STDOUT_FILENO);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
	}
	if (i == 0 || cmd[i + 1].cmd == NULL)
		close(fd);
	if (i > 0)
		close(data->tmpfd);
	execve(cmd[i].path, cmd[i].cmd, data->env);
}

void	exec_cmd(t_cmd *cmd, int ac, char **av, char **ev)
{
	t_data	*data;
	pid_t	*pid;

	data = init_data(cmd, ac, av, ev);
	pid = (pid_t *)malloc(sizeof(pid_t) * ft_strlen(*cmd->cmd));
	while (cmd[data->i].cmd != NULL)
	{
		if (cmd[data->i + 1].cmd != NULL)
			pipe(data->pipefd);
		pid[data->i] = fork();
		if (pid[data->i] == -1)
			exit_error("Error: fork failed\n", cmd, NULL);
		else if (pid[data->i] == 0)
			exec_child(cmd, data, data->i);
		else if (pid[data->i] > 0)
		{
			data->tmpfd = dup(data->pipefd[0]);
			close(data->pipefd[0]);
			close(data->pipefd[1]);
		}
		data->i++;
	}
	data->i = 0;
	while (cmd[data->i].cmd != NULL)
	{
		waitpid(pid[data->i], 0, WUNTRACED);
		data->i++;
	}
	free(pid);
}
