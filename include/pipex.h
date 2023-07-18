/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:12:34 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/18 14:39:19 by jhurpy           ###   ########.fr       */
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

typedef struct s_data
{
	char	*infile;
	char	*outfile;
	int		pipefd[2];
	int		tmpfd;
	char	**cmd;
	int		len;
	int		signal;
	pid_t	*pid;
}				t_data;

void	pipex_file(char **env, t_data *data);
void	execute_cmd(char *av, char **ev, t_data *data);
void	free_struct(t_data *data);
void	error(char *str, char *cmd_str, char **cmd, int flag);

#endif
