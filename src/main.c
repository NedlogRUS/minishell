/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apanikov <apanikov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 19:33:46 by apanikov          #+#    #+#             */
/*   Updated: 2023/07/12 19:43:01 by apanikov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// its code just for testing makefile
int main(int ac, char **av)
{
	int i = 0;
	if(ac != 2)
	{
		write(1, "ONLY ONE ARG", 12);
		return 0;
	}
	i = ft_atoi(av[1]);
	ft_putnbr_fd(i, 1);
	return 0;
}
