/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_execute_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/19 02:06:47 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/21 00:09:09 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	error(char *str, char *cmd_str, char **cmd)
{
	ft_putstr_fd(str, STDERR_FILENO);
	ft_putstr_fd(cmd_str, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (cmd != NULL)
		free(cmd);
	if (access("here_doc", F_OK) == 0)
		unlink("here_doc");
	exit(EXIT_FAILURE);
}

static char	*check_path_array(char *av, char **path_array)
{
	char	*tmp_path;
	char	*path;

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

static char	*get_path(char *av, char **ev)
{
	char	*path;
	char	**path_array;

	if (av[0] == '/')
	{
		path = ft_strdup(av);
		if (path == NULL)
			exit_error("Error: malloc failed ");
	}
	else
	{
		while (ft_strncmp(*ev, "PATH=", 5) != 0)
			ev++;
		path_array = ft_split(*ev, ':');
		if (path_array == NULL)
			exit_error("Error: malloc failed ");
		path = check_path_array(av, path_array);
		free(path_array);
	}
	return (path);
}

void	execute_cmd(char *av, char **ev)
{
	char	*path;
	char	**cmd;

	if (av == NULL || ft_strlen(av) == 0)
		exit_error("Error: command not found ");
	cmd = ft_split(av, ' ');
	if (cmd == NULL)
		exit_error("Error: malloc failed ");
	if (cmd[0] == NULL)
		error("Error: command not found: ", cmd[0], cmd);
	path = get_path(cmd[0], ev);
	if (path == NULL)
		error("Error: command not found: ", cmd[0], cmd);
	if (access(path, F_OK) == -1)
	{
		free(path);
		error("Error: no such file or directory: ", cmd[0], cmd);
	}
	else if (execve(path, cmd, ev) == -1)
		perror("Error: execve failed");
}
