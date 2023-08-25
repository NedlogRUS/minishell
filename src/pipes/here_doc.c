/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:32:58 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/25 20:36:18 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

static void	finalise_heredoc(t_mhstruct *mh, int *hdpipe)
{
	close(hdpipe[1]);
	if (num_of_heredoc(mh->token) >= 2)
	{
		close(hdpipe[0]);
		dup2(mh->in, STDIN_FILENO);
	}
	dup2(hdpipe[0], STDIN_FILENO);
	close(hdpipe[0]);
}

void	do_here_doc(char *lim, t_mhstruct *mh)
{
	int		hdpipe[2];
	char	*buffer;

	if (pipe(hdpipe) == -1)
		error_msg2("Error\nPipe Creation Failed\n");
	while (1)
	{
		buffer = NULL;
		buffer = readline(">");
		if (buffer != NULL)
		{
			if (!ft_strcmp(buffer, lim))
			{
				free(buffer);
				break ;
			}
			write(hdpipe[1], buffer, ft_strlen(buffer));
			write(hdpipe[1], "\n", 1);
			free(buffer);
		}
		if (buffer == NULL)
			break ;
	}
	finalise_heredoc(mh, hdpipe);
}
