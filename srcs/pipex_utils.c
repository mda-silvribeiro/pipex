/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-silv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 12:44:42 by mda-silv          #+#    #+#             */
/*   Updated: 2021/07/26 13:00:35 by mda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/pipex.h"

static void	ft_cmdpath(char *cmd, t_aux *src)
{
	char	**run;

	run = ft_split(cmd, ' ');
	src->cmd[0] = ft_strjoin("/bin/", run[0]);
	src->cmd[1] = ft_strjoin("/sbin/", run[0]);
	src->cmd[2] = ft_strjoin("/usr/bin/", run[0]);
	src->cmd[3] = ft_strjoin("/usr/sbin/", run[0]);
	src->cmd[4] = ft_strjoin("/usr/local/bin/", run[0]);
	src->argv = (char *const *)run;
	src->envp = NULL;
}

void	run_cmd(char *cmd)
{
	int		i;
	t_aux	*src;

	src = (t_aux *)malloc(sizeof(t_aux));
	i = 0;
	ft_cmdpath(cmd, src);
	while (i < 5)
		execve(src->cmd[i++], src->argv, src->envp);
	perror(src->argv[0]);
	free(src);
	exit(1);
}

void	ft_pipeEnd(int pipefd[2])
{
	close(pipefd[0]);
	close(pipefd[1]);
}

int	ft_stdout(const char *file)
{
	int	fd;

	fd = open(file, O_RDWR | O_CREAT, 0777);
	if (fd <= -1)
	{
		ft_error(-1);
		return (-1);
	}
	dup2(fd, 1);
	close(fd);
	return (0);
}

int	ft_stdin(const char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd <= -1)
	{
		ft_error(-1);
		return (-1);
	}
	dup2(fd, 0);
	close(fd);
	return (0);
}
