/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:40:09 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/29 18:40:13 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	exit_num_req(t_mhstruct *mh, const char *data)
{
	(void) mh;
	ft_putstr_fd("exit\n", 1);
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd((char *)data, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	exit(255);
}

int	check_long_min(const char *str)
{
	char	*line;
	char	*tmp;

	line = ft_strdup((char *) str);
	tmp = line;
	while (*tmp == 32 || (*tmp > 8 && *tmp < 14))
		tmp++;
	if ((!ft_strcmp(tmp, "-9223372036854775808")))
	{
		free(line);
		return (0);
	}
	free(line);
	return (1);
}
