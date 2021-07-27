/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-silv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 12:47:05 by mda-silv          #+#    #+#             */
/*   Updated: 2021/07/26 13:43:42 by mda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

int	pipex(char **av)
{
	int		fd[2];
	pid_t	pid;

	if (pipe(fd) == -1)
		return (0);
	pid = fork();
	if (pid == 0)
	{
		ft_stdin(av[1]);
		dup2(fd[1], 1);
		ft_pipeEnd(fd);
		run_cmd(av[2]);
	}
	else if (pid > 0)
	{
		wait(NULL);
		ft_stdout(av[4]);
		dup2(fd[0], 0);
		ft_pipeEnd(fd);
		run_cmd(av[3]);
	}
	return (0);
}

int	main(int ac, char **av)
{
	pid_t	pid;

	if (ac != 5)
		ft_error(-2);
	pid = fork();
	if (pid < 0)
		ft_error(-3);
	if (pid > 0)
		wait(NULL);
	else if (pid == 0)
		pipex(av);
	return (0);
}
