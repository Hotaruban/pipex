/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:45:46 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/11 23:57:38 by jhurpy           ###   ########.fr       */
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

typedef struct s_input
{
	int		ac;
	int		cmd_nbr;
	int		pipefd[2];
	int		tmpfd;
	int		status;
	char	**av;
	char	**ev;
	char	*infile;
	char	*outfile;
}		t_input;

typedef struct s_cmd
{
	char	**cmd;
	char	*path;
	int		status;
}		t_cmd;

char	*check_cmd_path(t_cmd *cmd, t_input *input, int i);
void	exec_cmd(t_cmd *cmd, t_input *input);

void	error(char *str, int status, t_cmd *cmd, t_input *input);
void	message_shell(t_cmd cmd);
void	free_struct(t_cmd *cmd);
void	free_2d_array(char **array);

#endif
