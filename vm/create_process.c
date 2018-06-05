/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_process.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjauzion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 15:38:10 by jjauzion          #+#    #+#             */
/*   Updated: 2018/06/05 16:24:08 by jjauzion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_process		*create_process(int address, int id, t_process *origin_process)
{
	t_process		*new_process;
	int				i;
	char			*tmp;

	if (!(new_process = (t_process*)ft_memalloc(sizeof(t_process))))
		return (error_ptr(NULL, "new process malloc error"));
	new_process->pc = address;
	i = (REG_SIZE > 4) ? 3 : REG_SIZE - 1;
	tmp = (char*)&id;
	while (i >= 0)
	{ 
		new_process->reg[0][i] = *tmp;
		tmp++;
		i--;
	}
	if (origin_process != NULL)
	{
		i = -1;
		while (++i < REG_NUMBER)
			ft_memcpy(new_process->reg[i], origin_process->reg[i], REG_SIZE);
		new_process->carry = origin_process->carry;
	}
	new_process->next = NULL;
	return (new_process);
}