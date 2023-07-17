/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_pipe_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 00:33:46 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/17 17:32:07 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	open_file(t_data *data, int flag)
{
	int fd;

	if (flag == 0)
	{
		fd = open(data->infile, O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else
	{
		if (ft_strncmp(data->infile, "here_doc", 9) == 0)
			fd = open(data->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
		close(fd);
	}
}

static void	child_process(t_data *data, char **env, int i)
{
	if (i == 0)
		open_file(data, 0);
	if (data->cmd[i + 2] == NULL)
		open_file(data, 1);
	if (i > 0)
		dup2(data->tmpfd, STDIN_FILENO);
	if (data->cmd[i + 2] != NULL)
	{
		dup2(data->pipefd[1], STDOUT_FILENO);
		close(data->pipefd[0]);
		close(data->pipefd[1]);
	}
	if (i > 0)
		close(data->tmpfd);
	execute_cmd(data->cmd[i], env);
}

static void	parent_process(t_data *data)
{
	data->tmpfd = dup(data->pipefd[0]);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
}

void	pipex_file(char **env, t_data *data)
{
	pid_t	*pid;
	int		i;

	pid = (pid_t *)malloc(sizeof(pid_t) * (ft_strlen(*data->cmd) - 1));
	if (!pid)
		error("Error: malloc failed", NULL, 1);
	i = 0;
	while (data->cmd[i + 1] != NULL)
	{
		if (data->cmd[i + 2] != NULL)
			pipe(data->pipefd);
		pid[i] = fork();
		if (pid[i] == -1)
			error("Error: fork failed", NULL, 0);
		else if (pid[i] == 0)
			child_process(data, env, i);
		else if (pid[i] > 0)
			parent_process(data);
		i++;
	}
	i = -1;
	while (data->cmd[++i + 1] != NULL)
		waitpid(pid[i], 0, WUNTRACED);
	free(pid);
}
