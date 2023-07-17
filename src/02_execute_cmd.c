/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_execute_cmd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 05:12:26 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/17 19:40:34 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	*get_env(char *cmd, char *ev)
{
	char	**path_array;
	char	*path;
	size_t	len;
	int		i;

	path_array = ft_split(ev, ':');
	if (path_array == NULL)
		error("Error: malloc failed", NULL, 1);
	i = -1;
	while (path_array[++i] != NULL)
	{
		len = ft_strlen(path_array[i]) + ft_strlen(cmd) + 2;
		path = (char *)malloc(sizeof(char) * len + 1);
		if (path == NULL)
			error("Error: malloc failed", NULL, 1);
		ft_strlcpy(path, path_array[i], len);
		ft_strlcat(path, "/", len);
		ft_strlcat(path, cmd, len);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	free_2d(path_array);
	return (path);
}

static char	*get_path(char *av, char **ev)
{
	char	*path;
	int		i;

	path = NULL;
	if (av[0] == '/')
	{
		path = ft_strdup(av);
		if (path == NULL)
			error("Error: malloc failed", NULL, 1);
	}
	else
	{
		i = 0;
		while (ft_strncmp(ev[i], "PATH=", 5) != 0)
			i++;
		path = get_env(av, ev[i]);
	}
	return (path);
}

void	execute_cmd(char *av, char **ev)
{
	char	*path;
	char	**cmd;

	cmd = ft_split(av, ' ');
	if (cmd == NULL)
		error("Error: malloc failed", NULL, 1);
	path = get_path(cmd[0], ev);
	if (ft_strlen(cmd[0]) != 0 && cmd[0] != NULL && path == NULL)
		error("Error: command not found: ", cmd[0], 1);
	else if (ft_strlen(cmd[0]) == 0 && cmd[0] != NULL)
		error("Error: permission denied: ", cmd[0], 1);
	else if (access(path, F_OK) == -1)
		error("Error: no such file or directory: ", path, 1);
	else
	{
		if (execve(path, cmd, ev) == -1)
		{
			perror("Error: execve failed\n");
			free(path);
		}
	}
	free_2d(cmd);
	exit(EXIT_FAILURE);
}
