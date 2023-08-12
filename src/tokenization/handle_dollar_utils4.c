/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_utils4.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtavitia <vtavitia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 11:07:10 by vtavitia          #+#    #+#             */
/*   Updated: 2023/08/12 15:10:44 by vtavitia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vtavitia.h"

int	ft_strnstr_mod(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	if (needle[n] == '\0')
		return (-1);
	while (i < len && haystack[i])
	{
		if (i > 0 && haystack[i - 1] == '$')
		{
			while (haystack[i + n] == needle[n] && needle[n] != '\0'
				&& n + i < len)
				n++;
		}
		if (needle[n] == '\0')
			return (i);
		i++;
		n = 0;
	}
	return (-1);
}

void	finalise_newterm(t_token *new_t, t_token **curr, t_mhstruct *mh, int k)
{
	(void)mh;
	new_t->data[k] = '\0';
	new_t->next = (*curr)->next;
	(*curr)->data = ft_strdup(new_t->data);
	(*curr)->next = new_t->next;
	free(new_t->data);
}

int	found_dollar(t_mhstruct *mh)
{
	int		found;
	char	*charpid;
	char	*charerrnum;

	charpid = ft_itoa(mh->mh_pid);
	charerrnum = ft_itoa(mh->er_num);
	found = 0;
	found = ft_strlen(charpid);
	free(charpid);
	free(charerrnum);
	return (found);
}

int	found_err_num(t_mhstruct *mh)
{
	int		found;
	char	*charpid;
	char	*charerrnum;

	charpid = ft_itoa(mh->mh_pid);
	charerrnum = ft_itoa(mh->er_num);
	found = 0;
	found = ft_strlen(charerrnum);
	free(charpid);
	free(charerrnum);
	return (found);
}

void	slice_term(t_token **x, t_mhstruct *mh, int i, int termlen)
{
	int			size;
	t_token		*new_term;
	t_token		*current;

	(void)mh;
	current = init_token("", NULL_VAL);
	current->data = ft_strdup((*x)->data);
	current->next = (*x)->next;
	free((*x)->data);
	new_term = init_token("", NULL_VAL);
	size = ft_strlen((current)->data) - termlen;
	new_term->data = (char *)malloc(sizeof(char) * size + 1);
	if (!new_term)
		return ;
	new_term->data[do_copy_inject(&i, termlen, &new_term, &current)] = '\0';
	new_term->next = (current)->next;
	free((current)->data);
	free(current);
	(*x)->data = strdup(new_term->data);
	(*x)->next = new_term->next;
	(*x)->s_quote = new_term->s_quote;
	(*x)->d_quote = new_term->d_quote;
	free(new_term->data);
	free(new_term);
	i++;
}
