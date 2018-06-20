/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjauzion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 14:30:29 by jjauzion          #+#    #+#             */
/*   Updated: 2018/06/20 15:29:53 by tmerli           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include "stdio.h"

static	void	print_winner(t_arena *arena)
{
	int			winner;
	uintmax_t	last_live;
	int			i;

	winner = arena->nb_champion - 1;
	last_live = 0;
	i = -1;
	while (++i < arena->nb_champion)
	{
		if (arena->champions[i]->last_live_cycle > last_live)
		{
			winner = i;
			last_live = arena->champions[i]->last_live_cycle;
		}
	}
	ft_printf("Contestant %d, \"%s\", has won !\n",
			winner + 1, arena->champions[winner]->header.prog_name);
}

static	void	print_champions(t_arena *arena)
{
	int i;

	i = -1;
	ft_printf("Introducing contestants...\n");
	while (++i < arena->nb_champion)
		ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
				i + 1, arena->champions[i]->header.prog_size,
				arena->champions[i]->header.prog_name,
				arena->champions[i]->header.comment);
}

int				main(int argc, char **argv)
{
	t_arena		*arena;

	(void)argv;
	if (!(arena = (t_arena*)ft_memalloc(sizeof(t_arena))))
		return (ERROR);
	if ((arena->champions = check_input(argc, argv, arena)) == NULL)
		return (ERROR);
	if (!(arena->mem = (t_uchar*)ft_memalloc(MEM_SIZE)))
		return (error_int("main"));
	init_arena(arena);
	print_champions(arena);
	if (run_arena(arena) != ERROR)
		print_winner(arena);
	free(arena->mem);
	while (arena->nb_champion)
	{
		free(arena->champions[arena->nb_champion - 1]->code);
		free(arena->champions[arena->nb_champion - 1]);
		arena->nb_champion--;
	}
	free(arena->champions);
	free(arena->option);
	free(arena);
	return (SUCCESS);
}
