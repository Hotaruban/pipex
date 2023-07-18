/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:16:48 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/18 14:59:54 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	free_struct(t_data *data)
{
	if (data->pid)
		free(data->pid);
	free(data);
}

static t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		error("Error: malloc failed", NULL, NULL, 1);
	data->infile = av[1];
	data->outfile = av[ac - 1];
	data->tmpfd = -1;
	data->signal = 0;
	data->pid = NULL;
	if (ac >= 6 && ft_strncmp(av[1], "here_doc", 9) == 0)
	{
		data->cmd = av + 3;
		data->len = ac - 3;
	}
	else
	{
		data->cmd = av + 2;
		data->len = ac - 2;
	}
	return (data);
}

static void	here_doc(char **av)
{
	char	*line;
	int		fd;

	fd = open(av[1], O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1)
		error("Error: creat failed", av[1], NULL, 0);
	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, av[2], ft_strlen(av[2])) == 0
			&& ((ft_strlen(line) - 1) == ft_strlen(av[2])))
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd);
}

static void	argv_check(int ac, char **av)
{
	if (ac < 5)
		error("Error: too few arguments", NULL, NULL, 1);
	if (ft_strncmp(av[1], "here_doc", 9) == 0 && ac < 6)
		error("Error: too few arguments", NULL, NULL, 1);
	if (access(av[1], F_OK) == -1 && ft_strncmp(av[1], "here_doc", 9) != 0)
		error("Error: no such file or directory: ", av[1], NULL, 0);
	else if (access(av[1], R_OK) == -1 && ft_strncmp(av[1], "here_doc", 9) != 0)
		error("Error: permission denied: ", av[1], NULL, 1);
	if (access(av[ac - 1], W_OK) == -1 && access(av[ac - 1], F_OK) == 0)
		error("Error: permission denied: ", av[ac - 1], NULL, 1);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	int		signal;

	argv_check(ac, av);
	data = init_data(ac, av);
	if (ac >= 6 && ft_strncmp(av[1], "here_doc", 9) == 0)
		here_doc(av);
	pipex_file(env, data);
	if (access("here_doc", F_OK) == 0)
		unlink("here_doc");
	signal = data->signal;
	free_struct(data);
	return (WEXITSTATUS (signal));
}
