/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   03_free_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 02:33:05 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/11 22:51:57 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	message_shell(t_cmd cmd)
{
	if (cmd.status == 1)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putstr_fd(cmd.path, 2);
		ft_putstr_fd("\n", 2);
	}
	if (cmd.status == 2)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putstr_fd(cmd.cmd[0], 2);
		ft_putstr_fd("\n", 2);
	}
	if (cmd.status == 3)
	{
		ft_putstr_fd("permission denied: ", 2);
		ft_putstr_fd(cmd.path, 2);
		ft_putstr_fd("\n", 2);
	}
}

void	error(char *str, int status, t_cmd *cmd, t_input *input)
{
	(void)status;
	perror(str);
	if (cmd)
		free_struct(cmd);
	if (input)
		free(input);
	exit(EXIT_FAILURE);
}

void	free_2d_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	free_struct(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd[i].cmd != NULL)
	{
		free_2d_array(cmd[i].cmd);
		free(cmd[i].path);
		i++;
	}
	free(cmd);
}
