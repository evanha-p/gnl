/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: evanha-p <evanha-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 17:57:41 by evanha-p          #+#    #+#             */
/*   Updated: 2022/04/28 13:32:08 by evanha-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_savestring(char **line, char **saved, int fd, int ret)
{
	int		i;
	char	*temp;

	i = 0;
	if (ft_strchr(saved[fd], '\n'))
	{
		while (saved[fd][i] != '\n')
			i++;
		*line = ft_strsub(saved[fd], 0, i);
		temp = ft_strsub(saved[fd], (i + 1), (ft_strlen(saved[fd]) - i));
		ft_strclr(saved[fd]);
		ft_strdel(&saved[fd]);
		saved[fd] = temp;
		return (1);
	}
	*line = ft_strdup(saved[fd]);
	ft_strclr(saved[fd]);
	ft_strdel(&saved[fd]);
	if (ret == 0)
		return (0 + (**line != 0));
	return (1);
}

void	ft_joinandclean(char **saved, char *buffer, int fd)
{
	char	*temp;

	temp = ft_strjoin(saved[fd], buffer);
	ft_strclr(saved[fd]);
	ft_strdel(&saved[fd]);
	saved[fd] = temp;
}

int	get_next_line(const int fd, char **line)
{
	static char	*saved[MAX_FD];
	char		buffer[BUFF_SIZE + 1];
	int			ret;

	ret = 1;
	if (fd < 0 || fd > MAX_FD || !line)
		return (-1);
	if (saved[fd] && ft_strchr(saved[fd], '\n'))
		return (ft_savestring(line, saved, fd, ret));
	while (ret)
	{
		ret = read(fd, buffer, BUFF_SIZE);
		if (ret < 0)
			return (-1);
		buffer[ret] = '\0';
		if (!saved[fd])
			saved[fd] = ft_strdup(buffer);
		else
			ft_joinandclean(saved, buffer, fd);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (ft_savestring(line, saved, fd, ret));
}
