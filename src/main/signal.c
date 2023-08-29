/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:57:57 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/29 18:58:52 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	do_sigint(int i)
{
	(void)i;
	g_error = 1;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	do_sigint_fork(int i)
{
	(void)i;
	g_error = 1;
	write(1, "\n", 1);
}

void	do_sigquit(int i)
{
	(void)i;
	g_error = 130;
	ft_putstr_fd("Quit: 3\n", 2);
}
