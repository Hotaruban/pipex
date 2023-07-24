/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:44:00 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/25 02:07:24 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	**get_cmd(char *av)
{
	char	**cmd;

	if (av == NULL || ft_strlen(av) == 0)
		exit_error("pipex: ", "command not found");
	cmd = ft_split(av, ' ');
	if (cmd == NULL)
		exit_error("pipex", "malloc failed ");
	if (cmd[0] == NULL)
		exit_error("pipex: ", "command not found ");
	return (cmd);
}

static char	**get_env(char **ev)
{
	char	**array;

	array = NULL;
	while (*ev != NULL && ft_strncmp(*ev, "PATH=", 5) != 0)
		ev++;
	if (*ev == NULL)
		exit_error("pipex: ", "No such file or directory");
	if (ft_strncmp(*ev, "PATH=", 5) == 0)
	{
		array = ft_split(*ev + 5, ':');
		if (array == NULL)
			exit_error("pipex", "malloc failed ");
	}
	ft_putendl_fd(*array, 2);
	return (array);
}

static char	*check_path(char *av, char **ev)
{
	char	**path_array;
	char	*tmp_path;
	char	*path;

	path_array = get_env(ev);
	while (*path_array++ != NULL)
	{
		tmp_path = ft_strjoin(*path_array, "/");
		path = ft_strjoin(tmp_path, av);
		if (tmp_path != NULL)
			free(tmp_path);
		if (access(path, F_OK) == 0)
			return (path);
		if (path != NULL)
			free(path);
	}
	return (NULL);
}

static char	*get_path(char **cmd, char **ev)
{
	char	*path;

	path = NULL;
	if (cmd[0][0] == '/')
	{
		path = ft_strdup(cmd[0]);
	}
	else
		path = check_path(cmd[0], ev);
	if (path == NULL)
	{
		ft_putendl_fd(path, 2);
		exit_error("pipex: command not found: ", cmd[0]);
		//while (*cmd != NULL)
		//	free(*cmd++);
		//free(cmd);
	}
	if (access(path, F_OK) == -1)
	{
		//while (*cmd != NULL)
		//	free(*cmd++);
		free(cmd);
		exit_error("pipex: no such file or directory: ", path);
	}
	return (path);
}

void	execute_cmd(char *av, char **ev)
{
	char	**cmd;
	char	*path;

	cmd = get_cmd(av);
	path = get_path(cmd, ev);
	if (execve(path, cmd, ev) == -1)
	{
		//while (*cmd != NULL)
		//	free(*cmd++);
		free(cmd);
		free(path);
		exit_error("pipex: ", "execve failed ");
	}
}
