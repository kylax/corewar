/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_arena.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjauzion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 15:12:10 by jjauzion          #+#    #+#             */
/*   Updated: 2018/06/19 16:54:02 by jjauzion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

static t_process	*kill_process(t_arena *arena, t_process *last_process, t_process *tokill)
{
	if (arena->process == tokill)
	{
		arena->process = tokill->next;
		free(tokill); //free_process() ???
		return (arena->process);
	}
	last_process->next = tokill->next;
	free(tokill);
	return (last_process->next);
}

int					run_arena(t_arena *arena)
{
	t_process	*current_process;
	t_process	*last_process;
	int			i;

	current_process = arena->process;
	while (arena->process)
	{
		SPAM((arena, current_process, 10, 0));
		show_cycle(arena, current_process, 10, 0);
		current_process = arena->process;
		last_process = NULL;
		while (current_process)
		{
			SPAM((arena, current_process, 40, 0));
			if (current_process->op == NULL)
			{
				SPAM((arena, current_process, 45, 0));
				current_process->op = read_op_code(arena, current_process);
			}
			else if (arena->cycle + arena->last_check == current_process->exe_cycle)
				exec_op(current_process, arena);
			else
				SPAM((arena, current_process, 70, 0));
			if (arena->cycle == arena->cycle2die || arena->cycle2die <= 0)
			{
				if (current_process->last_live_cycle == 0)
				{
					SPAM((arena, current_process, 30, 0));
					current_process = kill_process(arena, last_process, current_process);
					arena->nb_process--;
				}
				else
				{
					current_process->last_live_cycle = 0;
					last_process = current_process;
					current_process = current_process->next;
				}
			}
			else
				current_process = current_process->next;
		}
		if (arena->cycle == arena->cycle2die || arena->cycle2die <= 0)
		{
			arena->nb_check++;
			arena->last_check += arena->cycle;
			arena->cycle = 0;
			current_process = arena->process;
			i = -1;
			while (++i < arena->nb_champion)
			{
				SPAM((arena, current_process, 20, i));
				arena->champions[i]->nb_live = 0;
			}
			if (arena->nb_live >= NBR_LIVE || arena->nb_check >= MAX_CHECKS)
			{
				arena->cycle2die -= CYCLE_DELTA;
				arena->nb_check = 0;
			}
			arena->nb_live = 0;
		}
		SPAM((arena, current_process, 80, 0));
		if (print_dump_mem(arena))
			return (ERROR);
		arena->cycle++;
		show_cycle(arena, current_process, 85, 0);
	}
	SPAM((arena, current_process, 90, 0));
	return (SUCCESS);
}
