/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jjauzion <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:14:05 by jjauzion          #+#    #+#             */
/*   Updated: 2018/06/05 16:21:05 by jjauzion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft/ft_printf.h"

int	main()
{

	char test[4];
	char *tmp;
	int i;
	int j;

	j = 3;
	i = 10;
	tmp = (char*)&i;
	while (j >= 0)
	{
		test[j] = *tmp;
		tmp++;
		j--;
	}
	ft_print_mem(test, 4);
}