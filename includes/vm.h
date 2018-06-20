/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjauzion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 14:02:07 by jjauzion          #+#    #+#             */
/*   Updated: 2018/06/20 15:17:03 by jjauzion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H

# include "op.h"
# include "ft_printf.h"

# define SUCCESS 0
# define PID_MAX 2147483648
# define REG_LENGTH 1

# define S_UINT sizeof(unsigned int)
# define S_SHORT sizeof(short)

#if 0
# define SPAM(a) verbose a
# define SPAM2(a) ft_print_mem a
# define SPAM3(a) getchar a
#else
# define SPAM(a) (void)0
# define SPAM2(a) (void)0
# define SPAM3(a) (void)0
#endif

typedef unsigned char	t_uchar;
typedef unsigned int	t_uint;

# define VALID_OPT "avcopl"
# define VALID_OPT_WITH_VAL "d"

typedef struct			s_option
{
	int				option;
	int				d_cycle;
}						t_option;

typedef	struct			s_op
{
	char			*name;
	int				nb_arg;
	int				arg_type[3];
	int				op_code;
	int				nb_cycle;
	char			*def;
	t_uchar			ocp;
	int				dir_size;
}						t_op;

typedef struct			s_process
{
	t_uchar				reg[REG_NUMBER][REG_SIZE];
	t_uint				pid;
	int					pc;
	t_uchar				carry;
	int					exe_cycle;
	t_op				*op;
	int					op_size;
	char				op_idx_mod;
	int					exe_op;
	uintmax_t			last_live_cycle;
	struct s_process	*next;
}						t_process;

typedef struct			s_champion
{
	int			id;
	int			nb_live;
	header_t	header;
	t_uchar		*code;
	uintmax_t	last_live_cycle;
}						t_champion;

typedef struct			s_arena
{
	t_option		*option;
	t_uchar			*mem;
	int				cycle;
	int				cycle2die;
	int				last_check;
	int				nb_check;
	int				nb_process;
	t_champion		**champions;
	int				nb_champion;
	t_process		*process;
	int				nb_live;
}						t_arena;

typedef struct			s_op_fct
{
	int		op_code;
	int		(*fct)(t_process *process, t_arena *arena);
}						t_op_fct;

extern t_op				g_op_tab[17];
extern t_op_fct			g_op_fct_tab[];

void					*error_ptr(void *ptr, char *msg);
int						error_int(char *msg);
t_champion				*read_champ(char *file);
t_champion				**check_input(int argc, char **argv, t_arena *arena);
int						option(int *index, int argc, char **argv, t_option *option);
void					print_option(int option);
int						opt_is_set(int option, char test_opt);
int						init_arena(t_arena *arena, t_champion **champions);
t_process				*create_process(int address, int id, t_process *origin_process);
int						run_arena(t_arena *arena);
t_op					*read_op_code(t_arena *arena, t_process *process);
void					read_op(t_arena *arena, t_process *process);
int						exec_op(t_process *process, t_arena *arena);
void					print_arena(t_uchar *mem, size_t index, size_t length);
void					verbose(t_arena *arena, t_process *process, int step, int dump);
void					show_cycle(t_arena *arena, t_process *process, int step, int dump);
void					show_operation(t_arena *arena, t_process *process, int arg[3], char *msg);
void					show_pc_mouvement(t_arena *arena, t_process *process, int step, int dump);
int						print_dump_mem(t_arena *arena);

void					change_carry(t_process *process, int value);
int						get_address(int address);
t_uint					mem2int(t_uchar *mem, int index, int size);
void					int2mem(t_uchar *mem, int index, int value);
int						reg2int(t_process *process, t_uint reg);
int						int2reg(t_process *process, t_uint reg, int value);
int						get_arg_val(t_process *process, int arg_id, t_uchar *mem, int arg_index);
int						get_arg_id(t_process *process, int arg_id, t_uchar *mem, int arg_index);

int						ld(t_process *process, t_arena *arena);
int						lld(t_process *process, t_arena *arena);
int						ldi(t_process *process, t_arena *arena);
int						lldi(t_process *process, t_arena *arena);
int						st(t_process *process, t_arena *arena);
int						sti(t_process *process, t_arena *arena);
int						live(t_process *process, t_arena *arena);
int						zjmp(t_process *process, t_arena *arena);
int						and(t_process *process, t_arena *arena);
int						add(t_process *process, t_arena *arena);
int						sub(t_process *process, t_arena *arena);
int						or(t_process *process, t_arena *arena);
int						xor(t_process *process, t_arena *arena);
int						fork_op(t_process *process, t_arena *arena);
int						lfork_op(t_process *process, t_arena *arena);
int						aff(t_process *process, t_arena *arena);

#endif
