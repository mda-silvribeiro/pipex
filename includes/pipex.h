/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mda-silv <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/26 12:36:15 by mda-silv          #+#    #+#             */
/*   Updated: 2021/07/26 12:38:42 by mda-silv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct s_aux
{
	const char	*cmd[5];
	char *const	*argv;
	char *const	*envp;
}				t_aux;

void	*ft_calloc(size_t count, size_t size);
char	**ft_split(char const *s, char c);
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);
void	ft_error(int i);
int		main(int ac, char **av);
int		pipex(char **av);
int		ft_stdin(const char *file);
int		ft_stdout(const char *file);
void	run_cmd(char *cmd);
void	ft_pipeEnd(int pipefd[2]);

#endif
