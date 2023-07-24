/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:12:34 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/24 22:44:30 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/includes/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <sys/types.h>

int		check_args(int ac, char **av);
void	exit_error(char *str);
void	creat_here_doc(char *infile, char *limiter);
pid_t	*fork_process(int ac, char **av, char **ev, int index);
void	pipe_process(char *infile, int pipefd[2], int flag);
void	open_infile(char *infile, int pipefd[2]);
void	child_process(int pipefd[2], char **av, char **ev, int index);
void	open_outfile(char *outfile, int index);
void	execute_cmd(char *av, char **ev);
void	parent_process(int pipefd[2]);

#endif
