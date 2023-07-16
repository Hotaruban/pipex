/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_exec_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 00:33:46 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/17 04:44:47 by jhurpy           ###   ########.fr       */
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
	return (data);
}

static void	execute_cmd(t_cmd *cmd, t_data *data, int i)
{
	if (ft_strlen(cmd[i].cmd[0]) != 0 && cmd[i].cmd[0] != NULL
		&& cmd[i].path == NULL)
	{
		free(data);
		error_msg("command not found: ", cmd[i].cmd[0], NULL, NULL);
		exit_error(NULL, cmd, NULL);
	}
	if (ft_strlen(cmd[i].cmd[0]) == 0 && cmd[i].cmd[0] != NULL)
	{
		free(data);
		error_msg("permission denied: ", cmd[i].cmd[0], NULL, NULL);
		exit_error(NULL, cmd, NULL);
	}
	if (access(cmd[i].path, F_OK) == -1)
	{
		free(data);
		error_msg("no such file or directory: ", cmd[i].path, NULL, NULL);
		exit_error(NULL, cmd, NULL);
	}
	execve(cmd[i].path, cmd[i].cmd, data->env);
}

static void	exec_child(t_cmd *cmd, t_data *data, int i)
{
	int		fd;

	if (i == 0)
	{
		fd = open(data->infile, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	if (cmd[i + 1].cmd == NULL)
	{
		fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
	if (i > 0)
		dup2(data->tmpfd, STDIN_FILENO);
	if (cmd[i + 1].cmd != NULL)
	{
		dup2(data->pipefd[1], STDOUT_FILENO);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
	}
	if (i > 0)
		close(data->tmpfd);
	execute_cmd(cmd, data, i);
}

static void	dup_close(t_data *data)
{
	data->tmpfd = dup(data->pipefd[0]);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
}

void	exec_cmd(t_cmd *cmd, int ac, char **av, char **ev)
{
	t_data	*data;
	pid_t	*pid;
	int		i;

	data = init_data(cmd, ac, av, ev);
	pid = (pid_t *)malloc(sizeof(pid_t) * ft_strlen(*cmd->cmd));
	i = -1;
	while (cmd[++i].cmd != NULL)
	{
		if (cmd[i + 1].cmd != NULL)
			pipe(data->pipefd);
		pid[i] = fork();
		if (pid[i] == -1)
			exit_error("Error: fork failed\n", cmd, NULL);
		else if (pid[i] == 0)
			exec_child(cmd, data, i);
		else if (pid[i] > 0)
			dup_close(data);
	}
	i = -1;
	while (cmd[++i].cmd != NULL)
		waitpid(pid[i], 0, WUNTRACED);
	free(pid);
}
