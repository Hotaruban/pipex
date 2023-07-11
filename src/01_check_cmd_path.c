/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   01_check_cmd_path.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 00:14:57 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/11 23:55:42 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static char	**get_path(t_cmd *cmd, t_input *input)
{
	int		i;
	char	*path;
	char	**path_array;

	i = 0;
	while (input->ev[i] != NULL)
	{
		if (ft_strncmp(input->ev[i], "PATH=", 5) == 0)
		{
			path = ft_substr(input->ev[i], 5, ft_strlen(input->ev[i]) - 5);
			if (path == NULL)
				error("malloc", errno, cmd, input);
			path_array = ft_split(path, ':');
			if (path_array == NULL)
				error("malloc", errno, cmd, input);
			free(path);
			return (path_array);
		}
		i++;
	}
	return (NULL);
}

static char	*test_path(char *path_a, t_cmd *cmd, t_input *input, int i)
{
	char	*tmp;
	char	*path;

	path = NULL;
	tmp = path_a;
	path = ft_strjoin(tmp, "/");
	if (path == NULL)
		error("malloc", errno, cmd, input);
	free(tmp);
	tmp = path;
	path = ft_strjoin(tmp, cmd[i].cmd[0]);
	if (path == NULL)
		error("malloc", errno, cmd, input);
	free(tmp);
	return (path);
}

static char	*find_path(t_cmd *cmd, t_input *input, int i)
{
	int		j;
	char	*path;
	char	**path_array;

	path_array = get_path(cmd, input);
	if (path_array == NULL)
		cmd[i].status = 1;
	j = 0;
	path = NULL;
	while (path_array[j] != NULL)
	{
		path = test_path(path_array[j], cmd, input, i);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
		j++;
	}
	if (path == NULL && cmd[i].status == 0)
		cmd[i].status = 2;
	return (path);
}

static void	change_cmd(t_cmd *cmd, t_input *input, int i)
{
	char	*ptr;
	char	*tmp;
	int		len_cmd;

	ptr = ft_strrchr(cmd[i].cmd[0], '/');
	ptr++;
	len_cmd = ft_strlen(ptr);
	tmp = (char *)malloc(sizeof(char) * (len_cmd + 1));
	if (tmp == NULL)
		error("malloc", errno, cmd, input);
	ft_strlcpy(tmp, ptr, len_cmd + 1);
	free(cmd[i].cmd[0]);
	cmd[i].cmd[0] = tmp;
}

char	*check_cmd_path(t_cmd *cmd, t_input *input, int i)
{
	char	*path;
	int		len;

	if (cmd[i].cmd[0][0] == '/')
	{
		len = ft_strlen(cmd[i].cmd[0]);
		path = (char *)malloc(sizeof(char) + (len + 1));
		if (path == NULL)
			error("malloc", errno, cmd, input);
		ft_strlcpy(path, cmd[i].cmd[0], len + 1);
		if (access(cmd[i].cmd[0], F_OK) != 0)
			cmd[i].status = 1;
		change_cmd(cmd, input, i);
	}
	else
		path = find_path(cmd, input, i);
	if (access(cmd[i].cmd[0], F_OK) == -1 && cmd[i].status == 0)
		cmd[i].status = 3;
	return (path);
}
