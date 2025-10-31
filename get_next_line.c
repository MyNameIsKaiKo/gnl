/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleray <marvin@d42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 12:40:51 by jleray            #+#    #+#             */
/*   Updated: 2025/10/29 12:40:51 by jleray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buf	*ft_bufnew(char *content)
{
	t_buf	*output;

	output = malloc(sizeof(t_buf));
	if (!output)
		return (NULL);
	output->buf = malloc(sizeof(char) * (ft_strlen(content) + 1));
	ft_strlcpy(output->buf, content, ft_strlen(content) + 1);
	output->next = NULL;
	return (output);
}

char	*get_next_line(int fd)
{
	static t_buf	*buflst;
	char			buf[BUFFER_SIZE + 1];
	int				size;
	char			*output;

	if (fd == -1)
		return (0);
	if (!(buflst))
	{
		read(fd, buf, BUFFER_SIZE);
		buflst = ft_bufnew(buf);
	}
	if (ft_strchr(buflst->buf, '\n'))
	{
		size = (ft_strlen(buflst->buf) - ft_strlen(ft_strchr(buflst->buf,
						'\n')));
		output = ft_substr(buflst->buf, 0, size);
		buflst->buf = ft_substr(buflst->buf, ft_strlen(output) + 1,
				ft_strlen(buflst->buf) - ft_strlen(output));
	}
	return (output);
}
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int	main(void)
{
	int		fd;
	int		i;
	char	*nl;
	char	*nl2;

	fd = open("test", O_RDONLY);
	if (fd == -1)
		return (1);
	i = 0;
	nl = get_next_line(fd);
	nl2 = get_next_line(fd);
	nl2 = get_next_line(fd);
	while (nl2[i])
	{
		write(1, &nl2[i], 1);
		i++;
	}
	close(fd);
	return (0);
}
