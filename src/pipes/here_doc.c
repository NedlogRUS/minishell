/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:32:58 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/31 13:11:08 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

void	finalise_heredoc_pipes(t_mhstruct *mh, int *hdpipe)
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

void	do_hd(int pipes[1000][2], int i, t_mhstruct **tmp)
{
	close_upto_i(pipes, i);
	if (check_heredoc(*tmp))
	{
		while (check_heredoc(*tmp))
		{
			just_heredoc(&((*tmp)->token), tmp);
			if (!(*tmp)->token)
				break ;
		}
	}
}

int	check_heredoc(t_mhstruct *mh)
{
	t_token	*curr;

	if (!mh || !mh->token->data)
		return (0);
	curr = mh->token;
	while (curr)
	{
		if (curr->type == D_LT)
			return (1);
		curr = curr->next;
	}
	return (0);
}

void	finalise_heredoc(t_mhstruct *mh, int *hdpipe)
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

	(void)mh;
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
