/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/10 12:45:46 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/11 18:52:41 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _PIPEX_
# define _PIPEX_

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
	int		fd_in;
	int		fd_out;
}		t_cmd;

char	*check_cmd_path(char **cmd, t_input *input);
void	exec_cmd(t_cmd *cmd, t_input *input);

void	free_struct(t_cmd *cmd);
void	free_2d_array(char **array);

#endif
