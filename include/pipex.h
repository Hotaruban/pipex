/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 14:12:34 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/17 04:23:42 by jhurpy           ###   ########.fr       */
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

typedef struct t_cmd
{
	char	**cmd;
	char	*path;

}				t_cmd;

typedef struct t_data
{
	char	**env;
	char	*infile;
	char	*outfile;
	int		tmpfd;
	int		pipefd[2];
	int		i;
}				t_data;

void	exec_cmd(t_cmd *cmd, int ac, char **av, char **ev);

void	error_msg(char *str1, char *str2, char *str3, char *str4);
void	exit_error(char *msg, t_cmd *cmd, char **array);
void	argv_check(int ac, char **av);
void	free_2d(char **array);
void	free_struct(t_cmd *cmd);

#endif
