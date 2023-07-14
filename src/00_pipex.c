/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:16:48 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/14 19:53:07 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static void	here_doc(char **av)
{
	char	*line;
	size_t	len;
	int		fd;

	fd = open(av[1], O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1)
		exit_error("Error: creat failed\n", NULL, NULL);
	len = ft_strlen(av[2]);
	while (1)
	{
		write(STDOUT_FILENO, "pipe heredoc> ", 14);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, av[2], len) == 0
			&& ((ft_strlen(line) - 1) == len))
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd);
}

static char	*valid_path(char **array, char *cmd, t_cmd *cmd_struct)
{
	int		i;
	char	*path;
	char	*tmp;

	i = -1;
	path = NULL;
	while (array[++i] != NULL && cmd != NULL)
	{
		tmp = array[i];
		path = ft_strjoin(tmp, "/");
		if (!path)
			exit_error("Error: malloc failed\n", cmd_struct, array);
		free(tmp);
		tmp = path;
		path = ft_strjoin(tmp, cmd);
		if (!path)
			exit_error("Error: malloc failed\n", cmd_struct, array);
		free(tmp);
		if (access(path, F_OK) == 0)
			return (path);
	}
	return (NULL);
}

static char	*get_path(char *cmd, char **ev, t_cmd *cmd_struct)
{
	int		i;
	char	*path;
	char	**path_array;

	i = -1;
	while (ev[++i] != NULL)
	{
		if (ft_strncmp(ev[i], "PATH=", 5) == 0)
		{
			path = ft_substr(ev[i], 5, ft_strlen(ev[i]) - 5);
			path_array = ft_split(path, ':');
			if (!path_array || !path)
			{
				if (path)
					free(path);
				exit_error("Error: malloc failed\n", cmd_struct, path_array);
			}
			path = valid_path(path_array, cmd, cmd_struct);
			if (path != NULL)
				return (free(path_array), path);
		}
	}
	return (free(path_array), NULL);
}

static t_cmd	*get_cmd_path(int ac, char **av, char **ev, int i)
{
	t_cmd	*cmd;

	cmd = (t_cmd *)malloc(sizeof(t_cmd) * (ac + 1));
	if (!cmd)
		exit_error("Error: malloc failed\n", NULL, NULL);
	while (++i < ac)
	{
		cmd[i].cmd = ft_split(av[i], ' ');
		if (!cmd[i].cmd)
			exit_error("Error: malloc failed\n", cmd, NULL);
		if (cmd[i].cmd[0] == NULL)
			cmd[i].cmd[0] = ft_strdup("");
		if (cmd[i].cmd[0][0] == '/')
		{
			cmd[i].path = ft_strdup(cmd[i].cmd[0]);
			free(cmd[i].cmd[0]);
			cmd[i].cmd[0] = ft_substr(ft_strrchr(cmd[i].path, '/'), 1,
					ft_strlen(ft_strrchr(cmd[i].path, '/')) + 1);
		}
		else
			cmd[i].path = get_path(cmd[i].cmd[0], ev, cmd);
		if (!cmd[i].cmd[0])
			exit_error("Error: malloc failed\n", cmd, NULL);
	}
	return (cmd);
}

int	main(int ac, char **av, char **ev)
{
	t_cmd	*cmd;

	argv_check(ac, av);
	if (ac >= 6 && ft_strncmp(av[1], "here_doc", 8) == 0
		&& ft_strlen(av[1]) == 8)
	{
		here_doc(av);
		cmd = get_cmd_path(ac - 4, &av[3], ev, -1);
	}
	else
		cmd = get_cmd_path(ac - 3, &av[2], ev, -1);
	exec_cmd(cmd, ac, av, ev);
	if (access("here_doc", F_OK) == 0)
		unlink("here_doc");
	free_struct(cmd);
	return (0);
}

/*

	int i = 0;
	while (cmd[i].cmd != NULL)
	{
		printf("cmd[%d].cmd[0] = %s\n", i, cmd[i].cmd[0]);
		printf("cmd[%d].cmd[1] = %s\n", i, cmd[i].cmd[1]);
		printf("cmd[%d].path = %s\n", i, cmd[i].path);
		i++;
	}

*/
