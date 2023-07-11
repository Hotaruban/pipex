/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_check_cmd_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 00:14:57 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/11 18:49:53 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	**get_path(char **envp)
{
	int		i;
	char	*path;
	char	**path_array;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
			if (path == NULL)
				return (NULL);
			path_array = ft_split(path, ':');
			if (path_array == NULL)
				return (NULL);
			free(path);
			return (path_array);
		}
		i++;
	}
	return (NULL);
}

static char	*test_path(char *path_array, char *cmd)
{
	char	*tmp;
	char	*path;

	path = NULL;
	tmp = path_array;
	path = ft_strjoin(tmp, "/");
	if (path == NULL)
		return (NULL);
	free(tmp);
	tmp = path;
	path = ft_strjoin(tmp, cmd);
	if (path == NULL)
		return (NULL);
	free(tmp);
	return (path);
}

static char	*find_path(char *cmd, char **envp)
{
	int		i;
	char	*path;
	char	**path_array;

	path_array = get_path(envp);
	if (path_array == NULL)
		return (NULL);
	i = 0;
	path = NULL;
	while (path_array[i] != NULL)
	{
		path = test_path(path_array[i], cmd);
		if (path == NULL)
			return (NULL);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
		i++;
	}
	if (path == NULL)
		return (NULL);
	return (path);
}

char	*change_cmd(char *cmd)
{
	char	*ptr;
	char	*tmp;
	int		len_cmd;

	ptr = ft_strrchr(cmd, '/');
	ptr++;
	len_cmd = ft_strlen(ptr);
	tmp = (char *)malloc(sizeof(char) * (len_cmd + 1));
	if (tmp == NULL)
		return (NULL);
	ft_strlcpy(tmp, ptr, len_cmd + 1);
	free(cmd);
	cmd = tmp;
	return (cmd);
}

char	*check_cmd_path(char **cmd, t_input *input)
{
	char	*path;
	int		len;

	if ((*cmd[0]) == '/')
	{
		len = ft_strlen(*cmd);
		path = (char *)malloc(sizeof(char) + (len + 1));
		if (path == NULL)
			// EXIT TO HANDLE
		ft_strlcpy(path, *cmd, len + 1);
		if (access(*cmd, F_OK) != 0)
			// EXIT TO HANDLE ACCESS
		*cmd = change_cmd(*cmd);
		if (*cmd == NULL)
			// EXIT TO HANDLE MALLOC
	}
	else
		path = find_path(*cmd, input->ev);
		if (path == NULL)
			// EXIT TO HANDLE
	return (path);
}
