/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_sub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spliesei <spliesei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 18:33:26 by spliesei          #+#    #+#             */
/*   Updated: 2018/06/12 15:47:01 by spliesei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	save_sub(t_params *params, int id, char *line)
{
	t_instr *tmp;

	init_instr(params);
	tmp = params->instr;
	while (tmp->next)
		tmp = tmp->next;
	tmp->id = id;
	tmp->opcode = 5;
	tmp->nbr_arg = 3;
	get_params(tmp, line);
	fill_arg_types(params, tmp);
	calc_ocp(tmp);
	calc_bytes(tmp);
	ft_printf("1: [%s], 2: [%s] 3: [%s]\n", tmp->arg[0], tmp->arg[1], tmp->arg[2]);
	ft_printf("1: [%d], 2: [%d] 3: [%d]\n", tmp->arg_type[0], tmp->arg_type[1], tmp->arg_type[2]);
	ft_printf("OCP: %d\n", tmp->ocp);
	ft_printf("Bytes: %d\n\n", tmp->nbr_bytes);
}