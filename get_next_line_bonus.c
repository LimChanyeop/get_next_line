/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clim <clim@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/12 11:27:39 by clim              #+#    #+#             */
/*   Updated: 2021/01/15 13:40:56 by clim             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int				if_more_line(char *backup_buf)
{
	int			i;

	i = 0;
	while (backup_buf[i])
	{
		if (backup_buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

int				sepr_line(char **backup_buf, int idx, char **line)
{
	char		*temp;

	(*backup_buf)[idx] = 0;
	*line = ft_strdup(*backup_buf);
	if (!ft_strlen(&(*backup_buf)[idx + 1]))
	{
		free(*backup_buf);
		*backup_buf = 0;
		return (1);
	}
	temp = ft_strdup(&(*backup_buf)[idx + 1]);
	free(*backup_buf);
	*backup_buf = temp;
	return (1);
}

int				after_read_all(char **backup_buf, char **line, int byte_read)
{
	int			idx;

	if (byte_read < 0)
		return (-1);
	if (*backup_buf && (idx = if_more_line(*backup_buf)) >= 0)
		return (sepr_line(backup_buf, idx, line));
	else if (*backup_buf)
	{
		*line = *backup_buf;
		*backup_buf = 0;
		return (0);
	}
	*line = ft_strdup("");
	return (0);
}

int				get_next_line(int fd, char **line)
{
	static char	*backup_buf[OPEN_MAX];
	char		buf[BUFFER_SIZE + 1];
	int			byte_read;
	int			idx;
	char		*temp;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	while ((byte_read = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		temp = backup_buf[fd];
		buf[byte_read] = 0;
		backup_buf[fd] = ft_strjoin(backup_buf[fd], buf);
		if (temp)
			free(temp);
		idx = if_more_line(backup_buf[fd]);
		if (idx >= 0)
			return (sepr_line(&backup_buf[fd], idx, line));
	}
	return (after_read_all(&backup_buf[fd], line, byte_read));
}
