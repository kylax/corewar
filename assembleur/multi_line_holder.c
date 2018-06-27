//header

#include "asm.h"

char	*multi_line_holder(int fd, char *line)
{
	if (!ft_strncmp(line, COMMENT_CMD_STRING,
				ft_strlen(COMMENT_CMD_STRING)))
	{
		if (ft_strchr(ft_strchr(line, '"') + 1, '"'))
			return (line);
		else
			return (get_all_comment_line(fd, line));
	}
	else if (!ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
	{
		if (ft_strchr(ft_strchr(line, '"') + 1, '"'))
			return (line);
		else
			return (get_all_name_line(fd, line));
	}
	else
		exit(0);
}
