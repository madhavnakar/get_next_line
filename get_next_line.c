/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnakar <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/02 10:19:31 by mnakar            #+#    #+#             */
/*   Updated: 2018/07/04 17:50:16 by mnakar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		gnl_help(char **tab, char **line, int fd)
{
	char	*tmp;
	int		ind;

	ind = 0;
	while (tab[fd][ind] && tab[fd][ind] != '\n')
		ind++;
	if (!tab[fd][ind])
	{
		*line = ft_strdup(tab[fd]);
		ft_strdel(&tab[fd]);
	}
	else if (tab[fd][ind] == '\n')
	{
		*line = ft_strsub(tab[fd], 0, ind);
		tmp = ft_strdup(tab[fd] + ind + 1);
		free(tab[fd]);
		tab[fd] = tmp;
		if (!tab[fd][0])
		{
			free(tab[fd]);
			tab[fd] = NULL;
		}
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static char	*tab[4096] = {0};
	char		buf[BUFF_SIZE + 1];
	char		*tmp;
	int			bytes;

	if (fd < 0 || line == NULL)
		return (-1);
	ft_bzero(buf, BUFF_SIZE + 1);
	while ((bytes = read(fd, buf, BUFF_SIZE)) > 0)
	{
		if (!tab[fd])
			tab[fd] = ft_strnew(0);
		if (!tab[fd] || !(tmp = ft_strjoin(tab[fd], buf)))
			return (-1);
		free(tab[fd]);
		tab[fd] = tmp;
		if (ft_strchr(buf, '\n'))
			break ;
		ft_bzero(buf, BUFF_SIZE + 1);
	}
	if (bytes < 0)
		return (-1);
	else if (bytes == 0 && (tab[fd] == 0 || tab[fd][0] == 0))
		return (0);
	return (gnl_help(tab, line, fd));
}
