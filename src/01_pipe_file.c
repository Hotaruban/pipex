/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_pipe_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 00:33:46 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/18 15:00:29 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	open_file(t_data *data, int flag)
{
	int	fd;

	if (flag == 0)
	{
		fd = open(data->infile, O_RDONLY);
		dup2(fd, STDIN_FILENO);
	}
	else
	{
		if (ft_strncmp(data->infile, "here_doc", 9) == 0)
			fd = open(data->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			fd = open(data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		dup2(fd, STDOUT_FILENO);
	}
	close(fd);
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
	if (data->cmd[i] == NULL || ft_strlen(data->cmd[i]) == 0)
	{
		free_struct(data);
		error("Error: command not found", NULL, NULL, 0);
	}
	execute_cmd(data->cmd[i], env, data);
}

static void	parent_process(t_data *data)
{
	data->tmpfd = dup(data->pipefd[0]);
	close(data->pipefd[0]);
	close(data->pipefd[1]);
}

void	pipex_file(char **env, t_data *data)
{
	int		i;

	data->pid = (pid_t *)malloc(sizeof(pid_t) * (data->len - 1));
	if (!data->pid)
		error("Error: malloc failed", NULL, NULL, 1);
	i = 0;
	while (data->cmd[i + 1] != NULL)
	{
		if (data->cmd[i + 2] != NULL)
			pipe(data->pipefd);
		data->pid[i] = fork();
		if (data->pid[i] == -1)
			error("Error: fork failed", NULL, NULL, 0);
		else if (data->pid[i] == 0)
			child_process(data, env, i);
		else if (data->pid[i] > 0)
			parent_process(data);
		i++;
	}
	i = -1;
	while (data->cmd[++i + 1] != NULL)
		waitpid(data->pid[i], &data->signal, WUNTRACED);
}
