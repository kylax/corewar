/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fct_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjauzion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 16:16:31 by jjauzion          #+#    #+#             */
/*   Updated: 2018/06/09 12:43:27 by jjauzion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_op_fct	g_op_fct_tab[] =
{
	//{1, live},
	{2, ld},
	{3, st},
/*	{4, add},
	{5, sub},
	{6, and},
	{7, or},
	{8, xor},
	{9, zjump},
*/	{10, ldi},
/*	{11, sti},
	{12, fork},
	{13, lld},
	{14, lldi},
	{15, lfork},
	{16, aff},*/
	{0, NULL}
};
