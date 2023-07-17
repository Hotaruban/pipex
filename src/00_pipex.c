/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   00_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/13 19:16:48 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/17 16:56:44 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

static t_data	*init_data(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		error("Error: malloc failed", NULL, 1);
	data->infile = av[1];
	data->outfile = av[ac - 1];
	data->tmpfd = -1;
	if (ac >= 6 && ft_strncmp(av[1], "here_doc", 9) == 0)
		data->cmd = av + 3;
	else
		data->cmd = av + 2;
	return (data);
}

static void	here_doc(char **av)
{
	char	*line;
	int		fd;

	fd = open(av[1], O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1)
		error("Error: creat failed", av[1], 0);
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
		error("Error: too few arguments", NULL, 1);
	if (ft_strncmp(av[1], "here_doc", 9) == 0 && ac < 6)
		error("Error: too few arguments", NULL, 1);
	if (access(av[1], F_OK) == -1 && ft_strncmp(av[1], "here_doc", 9) != 0)
		error("no such file or directory: ", av[1], 0);
	else if (access(av[1], R_OK) == -1 && ft_strncmp(av[1], "here_doc", 9) != 0)
		error("permission denied: ", av[1], 0);
	if (access(av[ac - 1], W_OK) == -1 && access(av[ac - 1], F_OK) == 0)
		error("permission denied: ", av[ac - 1], 0);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	argv_check(ac, av);
	data = init_data(ac, av);
	if (ac >= 6 && ft_strncmp(av[1], "here_doc", 9) == 0)
		here_doc(av);
	pipex_file(env, data);
	if (access("here_doc", F_OK) == 0)
		unlink("here_doc");
	free(data);
	return (0);
}
