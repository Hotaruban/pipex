/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   02_utils_pipex.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhurpy <jhurpy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 01:19:43 by jhurpy            #+#    #+#             */
/*   Updated: 2023/07/17 04:30:58 by jhurpy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	error_msg(char *str1, char *str2, char *str3, char *str4)
{
	ft_putstr_fd(str1, STDERR_FILENO);
	ft_putstr_fd(str2, STDERR_FILENO);
	ft_putstr_fd(str3, STDERR_FILENO);
	ft_putstr_fd(str4, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	exit_error(char *msg, t_cmd *cmd, char **array)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	if (access("here_doc", F_OK) == 0)
		unlink("here_doc");
	if (cmd != NULL)
		free_struct(cmd);
	if (array != NULL)
		free_2d(array);
	exit(EXIT_FAILURE);
}

void	argv_check(int ac, char **av)
{
	if (ac < 5)
		exit_error("Error: too few arguments\n", NULL, NULL);
	if (ft_strncmp(av[1], "here_doc", 9) == 0 && ac < 6)
		exit_error("Error: too few arguments\n", NULL, NULL);
	if (access(av[1], F_OK) == -1 && ft_strncmp(av[1], "here_doc", 9) != 0)
		error_msg("no such file or directory: ", av[1], NULL, NULL);
	else if (access(av[1], R_OK) == -1 && ft_strncmp(av[1], "here_doc", 9) != 0)
		error_msg("permission denied: ", av[1], NULL, NULL);
	if (access(av[ac - 1], W_OK) == -1 && access(av[ac - 1], F_OK) == 0)
		error_msg("permission denied: ", av[ac - 1], NULL, NULL);
}

void	free_2d(char **array)
{
	int	i;

	i = -1;
	while (array[++i] != NULL)
		free(array[i]);
	free(array);
}

void	free_struct(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (cmd[++i].cmd != NULL)
	{
		free_2d(cmd[i].cmd);
		free(cmd[i].path);
	}
	free(cmd);
}
