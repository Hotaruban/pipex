/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_execute_cmd_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/22 21:46:26 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/23 00:28:23 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include_bonus/pipex_bonus.h"

static void	free_exit_error(char *str, char **cmd, char *path)
{
	perror(str);
	if (cmd[1] != NULL)
	{
		while (*cmd != NULL)
			free(*cmd++);
	}
	else
		free(cmd);
	if (path != NULL)
		free(path);
	exit(EXIT_FAILURE);
}

static void	exit_error(char *str)
{
	perror(str);
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
			exit_error("malloc\n");
	}
	else
	{
		while (ft_strncmp(*ev, "PATH=", 5) != 0)
			ev++;
		path_array = ft_split(*ev, ':');
		if (path_array == NULL)
			exit_error("malloc\n");
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
		exit_error(av);
	cmd = ft_split(av, ' ');
	if (cmd == NULL)
		exit_error("malloc\n");
	if (cmd[0] == NULL)
		free_exit_error(cmd[0], cmd, NULL);
	path = get_path(cmd[0], ev);
	if (path == NULL)
		free_exit_error(NULL, cmd, NULL);
	if (access(path, F_OK) == -1)
		free_exit_error(path, cmd, path);
	else if (execve(path, cmd, ev) == -1)
		free_exit_error("execve\n", cmd, path);
}
