/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:33:46 by apanikov          #+#    #+#             */
/*   Updated: 2023/07/14 16:01:10 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int main(int ac, char **av, char **env)
{
	(void) env;
	(void) ac;
	(void) av;
	t_mhstruct *mh;
	mh = malloc(sizeof(t_mhstruct));
	
	while(1)
	{
		mh->input = readline("$> ");
		printf("%s\n", mh->input);
		add_history(mh->input);
	}
	return 0;
}
