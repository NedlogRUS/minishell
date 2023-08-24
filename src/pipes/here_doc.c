/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:32:58 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/23 18:50:30 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

static int	read_line(char **buffer)
{
	char	*tmp;
	int		i;
	int		bytes;
	char	c;

	i = 0;
	bytes = 0;
	tmp = (char *)malloc(sizeof(char) * 9999);
	if (!tmp)
		return (1);
	bytes = read(0, &c, 1);
	while (bytes > 0 && c != '\n' && c != '\0')
	{
		if (c != '\n' || c != '\0')
			tmp[i] = c;
		i++;
		bytes = read(0, &c, 1);
	}
	if (bytes > 0)
		tmp[i] = '\n';
	tmp[++i] = '\0';
	*buffer = tmp;
	return (bytes);
}

static void	here_doc_child(char **buff, char *lim, int *hdpipe)
{
	char	*buffer;

	buffer = *buff;
	close(hdpipe[0]);
	ft_putstr_fd("> ", 1);
	while (read_line(&buffer))
	{
		// signal(SIGINT, do_sigint_fork);
		// signal(SIGQUIT, SIG_IGN);
		if (!(ft_strncmp(buffer, lim, ft_strlen(lim)) == 0))
			ft_putstr_fd("> ", 1);
		if (ft_strncmp(buffer, lim, ft_strlen(lim)) == 0)
		{
			free(buffer);	
			exit(0);
		}
		write(hdpipe[1], buffer, ft_strlen(buffer));
		free(buffer);
	}
	close(hdpipe[1]);
	exit(0);
}

void do_sigquit_leha(int i)
{
	(void)i;
	GLOBAL_ERROR = 130;
	rl_redisplay();
}

void	do_here_doc(char *lim)
{
	int		hdpipe[2];
	int		pid;
	char	*buffer;

	if (pipe(hdpipe) == -1)
		error_msg2("Error\nPipe Creation Failed\n");
	pid = fork();
	// signal(SIGINT, do_sigint_fork);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, do_sigquit_leha);
	if (pid == 0)
	{
		signal(SIGINT, do_sigint_fork);
		signal(SIGQUIT, do_sigquit_leha);
		here_doc_child(&buffer, lim, hdpipe);
	}
	else
	{
		wait(NULL);
		close(hdpipe[1]);
		dup2(hdpipe[0], STDIN_FILENO);
		close(hdpipe[0]);
	}
}
