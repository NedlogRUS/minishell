/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:33:46 by apanikov          #+#    #+#             */
/*   Updated: 2023/08/30 17:26:46 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_program_banner(void)
{
	printf("\x1b[38;2;255;165;0m");
	printf("    +                +    )       (     (  +  \n");
	printf("   (    +      +      ( /(    +  )\\ )  )\\ )  \n");
	printf("    )   (   +     (   )\\()) (   (()/( (()/(  \n");
	printf("   (    )\\   (    )\\ ((_)\\  )\\   /(_)) /(_)) \n");
	printf(" + )\\  ((_)  )\\ )((_) _((_)((_) (_))  (_))   \n");
	printf(" _((_)) (_) _(_/( (_)");
	printf("\x1b[31m");
	printf("| || || __|| |   | |    \n");
	printf("| '  \\  | || ' \\  | || __ || _| | |__ | |__  \n");
	printf("|_|_|_| |_||_||_| |_||_||_||___||____||____| \n");
	printf("\x1b[38;2;255;165;0m");
	printf("Version : 6.66 \n");
	printf("Authors : VTavitia & APanikov \n");
	printf("\x1b[0m");
}

void	execution_of_commands(t_mhstruct *mh)
{
	if (!ft_strcmp(mh->token->data, "pwd"))
		builtin_pwd(mh);
	else if (!ft_strcmp(mh->token->data, "env"))
		builtin_env(mh);
	else if (!ft_strcmp(mh->token->data, "export"))
		builtin_export(mh);
	else if (!ft_strcmp(mh->token->data, "unset"))
		builtin_unset(mh);
	else if (!ft_strcmp(mh->token->data, "cd"))
		builtin_cd(mh);
	else if (!ft_strcmp(mh->token->data, "echo"))
		builtin_echo(mh);
	else if (!ft_strcmp(mh->token->data, "exit"))
		builtin_exit(mh);
	else
		execve_of_commands(mh);
	return ;
}

void	free_env(t_env *env)
{
	t_env	*curr;
	t_env	*tmp;

	if (env == NULL)
		return ;
	curr = env;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->next;
		if (tmp->data != NULL)
			free(tmp->data);
		if (tmp->name != NULL)
			free(tmp->name);
		if (tmp != NULL)
			free(tmp);
	}
	env = NULL;
}

void	free_token_main(t_mhstruct *mh)
{
	t_token	*curr;
	t_token	*tmp;

	if (mh->token == NULL)
		return ;
	curr = mh->token;
	while (curr != NULL)
	{
		tmp = curr;
		curr = curr->next;
		if (tmp->data != NULL)
			free(tmp->data);
		if (tmp != NULL)
			free(tmp);
	}
	mh->token = NULL;
}

int	main(int ac, char **av, char **env)
{
	t_mhstruct	*mh;
	int			mark;

	g_error = 0;
	(void) av;
	mark = 0;
	if (ac > 1)
		exit (1);
	rl_catch_signals = 0;
	mh = malloc(sizeof(t_mhstruct));
	mh->token = NULL;
	initializer_mh(env, mh);
	print_program_banner();
	minihell(mh, mark);
	return (0);
}
