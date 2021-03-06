/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smortier <smortier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/03 16:41:31 by smortier          #+#    #+#             */
/*   Updated: 2018/06/28 10:09:15 by jjauzion         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"

t_lexer		*new_lexer(char *line)
{
	t_lexer		*new_lexer;

	if (!(new_lexer = (t_lexer *)ft_memalloc(sizeof(t_lexer))))
		exit(0);
	if (!(new_lexer->line = ft_strdup(line)))
		exit(0);
	return (new_lexer);
}

t_lexer		*create_lexer(t_params *params, char *line)
{
	t_lexer		*tmp;
	t_lexer		*save;

	if (params->lexer == NULL)
	{
		tmp = new_lexer(line);
		return (tmp);
	}
	else
	{
		tmp = params->lexer;
		save = tmp;
		if (!tmp)
		{
			ft_printf("Wrong file, please check instructions ...\n");
			exit(0);
		}
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new_lexer(line);
		return (save);
	}
}

char		*parse_line(char *line)
{
	char	*parsed;
	char	*tmp;
	int		index;

	parsed = line;
	if (ft_strchr(line, LABEL_CHAR))
	{
		index = -1;
		while (line[++index] && line[index] != LABEL_CHAR)
			;
		if (index && line[index - 1] && (line[index - 1] == ' ' ||
			line[index - 1] == '\t'))
			return (line);
		tmp = ft_strchr(line, LABEL_CHAR);
		if (!str_is_empty(tmp + 1) && line[index - 1] != DIRECT_CHAR)
		{
			return (tmp + 1);
		}
		else if (str_is_empty(tmp + 1))
			return ("    ");
	}
	return (line);
}

void		lexer(t_params *params)
{
	int		index;

	index = 0;
	while (pass_ws(params->file[index])[0] == '.')
		index += 1;
	index -= 1;
	while (params->file[++index])
	{
		if (params->file[index][ft_strlen(params->file[index]) - 1]
			== SEPARATOR_CHAR)
		{
			ft_printf("Error: Line %d ends with a ", index + 1);
			ft_printf("'%c'!\n", SEPARATOR_CHAR);
			exit(0);
		}
		params->lexer = create_lexer(params, parse_line(params->file[index]));
	}
}
