/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_tools.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spliesei <spliesei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 13:16:27 by spliesei          #+#    #+#             */
/*   Updated: 2018/06/21 16:35:13 by spliesei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

t_label	*get_label_by_pos(t_params *params, int pos)
{
	t_label		*tmp;

	tmp = params->label;
	while (tmp)
	{
		if (pos == tmp->pos)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

int		get_adress(t_params *params, int id)
{
	int			nb_bytes;
	t_instr		*tmp;

	nb_bytes = 0;
	tmp = params->instr;
	while (tmp)
	{
		if (id == tmp->id)
			return (nb_bytes);
		nb_bytes += tmp->nbr_bytes;
		tmp = tmp->next;
	}
	return (nb_bytes);
}

void	fill_value_label(t_params *params)
{
	t_label		*tmp;

	tmp = params->label;
	while (tmp)
	{
		tmp->value = get_adress(params, tmp->instr);
		tmp = tmp->next;
	}
}

int		zip_newline(t_lexer *tmp2, int index2)
{
	while (tmp2 && str_is_empty(tmp2->line))
	{
		index2 += 1;
		tmp2 = tmp2->next;
	}
	return (index2);
}

void	get_label_instr(t_params *params)
{
	t_lexer *tmp;
	t_lexer *tmp2;
	int		index;
	int		index2;

	tmp = params->lexer;
	index = 0;
	while (tmp)
	{
		index2 = 0;
		tmp2 = tmp;
		if (get_label_by_pos(params, index))
		{
			index2 = zip_newline(tmp2, index2);
			if (str_is_empty(tmp->line))
				get_label_by_pos(params, index)->instr = index + index2;
			else
				get_label_by_pos(params, index)->instr = index;
		}
		tmp = tmp->next;
		index++;
	}
	fill_value_label(params);
}
