/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minihell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 19:20:33 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/29 19:34:02 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	minihell2(t_mhstruct *mh, int mark)
{
	if (check_last_type(mh) || check_redir_pipe_syntax(mh))
		pr_err(mh, 2, gemsg("", mh->emsg[15], ""));
	else if (check_redir_exist(mh->token) && !(check_pipe_exists(mh->token)))
	{
		mark = do_redirects(mh->token, mh);
		if (ft_tokenlstsize(mh->token) && !mark)
			execution_of_commands(mh);
		dup2(mh->screen, STDOUT_FILENO);
		dup2(mh->in, STDIN_FILENO);
	}
	else if (check_pipe_exists(mh->token))
	{
		launch_pipes(&mh);
		dup2(mh->screen, STDOUT_FILENO);
		dup2(mh->in, STDIN_FILENO);
	}
	else if (ft_strlen(mh->token->data) && mh->token && \
		!(check_pipe_exists(mh->token)))
		execution_of_commands(mh);
	free_token_main(mh);
	free(mh->token);
}

void	free_helper(t_mhstruct *mh)
{
	free_token_main(mh);
	free(mh->token);
}

void	minihell(t_mhstruct *mh, int mark)
{
	while (1)
	{
		signal(SIGINT, do_sigint);
		signal(SIGQUIT, SIG_IGN);
		mh->input = readline("$> ");
		if (mh->input == NULL)
		{
			free(mh->input);
			printf("\x1b[1A\x1b[3Cexit\n");
			exit(g_error);
		}
		if (ft_strlen(mh->input))
		{
			add_history(mh->input);
			check_and_tokenize(mh);
			free(mh->input);
			if (mh->token)
				minihell2(mh, mark);
			else
				free_helper(mh);
		}
		else
			free(mh->input);
	}
}
