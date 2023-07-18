/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:33:46 by apanikov          #+#    #+#             */
/*   Updated: 2023/07/17 20:15:39 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		check_and_tokenize(mh);
		printf("%s\n", mh->input);
		add_history(mh->input);
		//break ;
	}
	//system("leaks minishell");
	return 0;
}