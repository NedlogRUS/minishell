/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 12:55:08 by vatchetavit       #+#    #+#             */
/*   Updated: 2023/08/05 14:13:30 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

static void	clean_buffer(char **buffer)
{
	int	i;

	i = 0;
	while ((*buffer)[i])
	{
		if ((*buffer)[i] == '\n')
		{
			(*buffer)[i] = '\0';
			break ;
		} 
		i++;
	}
}

static char	*get_command(char *str)
{
	int		i;
	char	*command;

	i = 0;
	while (str[i] != ' ' && str[i])
		i++;
	command = (char *)malloc(sizeof(char) * (i + 1));
	i = 0;
	while (str[i] != ' ' && str[i])
	{
		command[i] = str[i];
		i++;
	}
	command[i] = '\0';
	return (command);
}

static void	set_args(char **args, char *cmnd)
{
	args[0] = "/usr/bin/which";
	args[1] = cmnd;
	args[2] = NULL;
}

char	*find_path(char *comm, char **envp, char *buffer)
{
	int		pathpipe[2];
	int		pid;
	char	*args[3];
	char	*cmnd;

	pipe(pathpipe);
	cmnd = get_command(comm);
	pid = fork();
	if (pid == 0)
	{
		dup2(pathpipe[1], 1);
		set_args(args, cmnd);
		execve("/usr/bin/which", args, envp);
		perror("Command not found\n");
	}
	else
	{
		wait(NULL);
		close(pathpipe[1]);
		read(pathpipe[0], buffer, 1024);
		clean_buffer(&buffer);
		close(pathpipe[0]);
	}
	free (cmnd);
	return (buffer);
}
