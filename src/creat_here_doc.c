/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   creat_here_doc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:13:40 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/24 23:56:08 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	creat_here_doc(char *infile, char *limiter)
{
	char	*line;
	int		fd;

	fd = open(infile, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1)
		exit_error("pipex: ", infile);
	while (1)
	{
		write(STDOUT_FILENO, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& ((ft_strlen(line) - 1) == ft_strlen(limiter)))
			break ;
		write(fd, line, ft_strlen(line));
		free(line);
	}
	free(line);
	close(fd);
}
