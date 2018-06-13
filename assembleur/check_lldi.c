/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_lldi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spliesei <spliesei@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/11 13:07:37 by spliesei          #+#    #+#             */
/*   Updated: 2018/06/12 13:45:21 by spliesei         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void	check_nbr_arg_lldi(char **split)
{
	int		i;

	i = -1;
	while (split[++i])
		;
	if (i != 3)
	{
		ft_printf("Error:\n");
		exit(0);
	}
}

int		check_lldi_par(t_params *params, char *line, int index_line)
{
	char	**split;
	char	*arg1;
	char	*arg2;
	char	*arg3;
	int		index;

	split = ft_strsplit(line, SEPARATOR_CHAR);
	check_nbr_arg_lldi(split);
	arg1 = ft_strtrim(split[0]);
	arg2 = ft_strtrim(split[1]);
	arg3 = ft_strtrim(split[2]);
	index = -1;
	while (split[++index])
		ft_strdel(&split[index]);
	ft_memdel((void *)&split);
	if (!check_type(params, arg1))
	{
		ft_printf("Error: Wrong type of arg1 on instr %d (lldi)\n", index_line);
		exit(0);
	}
	if (check_type(params, arg2) != DIR_CODE && check_type(params, arg2) != IND_CODE)
	{
		ft_printf("Error: Wrong type of arg2 on instr %d (lldi)\n", index_line);
		exit(0);
	}
	if (check_type(params, arg3) != REG_CODE)
	{
		ft_printf("Error: Wrong type of arg3 on instr %d (lldi)\n", index_line);
		exit(0);
	}
	ft_strdel(&arg1);
	ft_strdel(&arg2);
	ft_strdel(&arg3);
	return (1);
}