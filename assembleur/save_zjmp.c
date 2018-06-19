/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_zjmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spliesei <spliesei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 18:45:02 by spliesei          #+#    #+#             */
/*   Updated: 2018/06/19 17:07:56 by spliesei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	save_zjmp(t_params *params, int id, char *line)
{
	t_instr	*tmp;

	init_instr(params);
	tmp = params->instr;
	while (tmp->next)
		tmp = tmp->next;
	tmp->id = id;
	tmp->opcode = 9;
	tmp->nbr_arg = 1;
	tmp->ocp = 0;
	get_params(tmp, line);
	fill_arg_types(params, tmp);
	calc_bytes(tmp);
	tmp->nbr_bytes -= 2;
	tmp->d2 = 1;
	// ft_printf("1: [%s]\n", tmp->arg[0]);
	// ft_printf("1: [%d]\n", tmp->arg_type[0]);
	// ft_printf("OCP: %d\n", tmp->ocp);
	// ft_printf("Bytes: %d\n\n", tmp->nbr_bytes);
}
