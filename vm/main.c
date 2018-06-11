/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjauzion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 14:30:29 by jjauzion          #+#    #+#             */
/*   Updated: 2018/06/11 11:23:48 by jjauzion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "stdio.h"

int		main(int argc, char **argv)
{
	t_arena		*arena;
	t_champion	**champions;
	int			i;

	(void)argv;
	if (!(arena = (t_arena*)ft_memalloc(sizeof(t_arena))))
		return (ERROR);
	if ((champions = check_input(argc, argv, arena)) == NULL)
		return (ERROR);
	if (!(arena->mem = (t_uchar*)ft_memalloc(MEM_SIZE)))
		return (error_int("main"));
	init_arena(arena, champions);
	ft_printf("Introducing contestants...\n");
	i = -1;
	while (++i < arena->nb_champion)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				i + 1, arena->champions[i]->header.prog_size,
				arena->champions[i]->header.prog_name,
				arena->champions[i]->header.comment);
	run_arena(arena);
	free(arena->mem);
	while (arena->nb_champion)
	{
		free(arena->champions[arena->nb_champion - 1]->code);
		free(arena->champions[arena->nb_champion - 1]);
		arena->nb_champion--;
	}
	free(arena->champions);
	return (SUCCESS);
}
