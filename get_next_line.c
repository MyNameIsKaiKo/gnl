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

t_buf	*bufclear(t_buf *buflst)
{
	char	*tmp;
	int		size;
	t_buf	*output;

	size = 0;
	if (is_nl(buflst))
	{
		while (size == 0)
		{
			if (ft_strchr(buflst->buf, '\n'))
				size = ft_strlen(ft_strchr(buflst->buf, '\n') + 1);
			if (size == 0)
				buflst = buflst->next;
		}
		tmp = malloc(sizeof(char) * (size + 1));
		ft_strlcat(tmp, ft_strchr(buflst->buf, '\n') + 1, size + 1);
	}
	else
	{
		tmp = malloc(sizeof(char) * 1);
		tmp = "";
	}
	output = ft_bufnew(tmp);
	free(tmp);
	return (output);
}

void	ft_bufadd_back(t_buf *lst, t_buf *new)
{
	t_buf	*tmp;

	if (!lst || !new)
		return ;
	if (!lst)
	{
		lst = new;
		return ;
	}
	tmp = lst;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_buf	*ft_bufnew(char *content)
{
	t_buf	*output;

	output = malloc(sizeof(t_buf));
	if (!output)
		return (NULL);
	output->buf = malloc(sizeof(char) * (ft_strlen(content) + 1));
	ft_strlcat(output->buf, content, ft_strlen(content) + 1);
	output->next = NULL;
	return (output);
}

char	*extract_line(t_buf *buflst)
{
	char	*output;
	int		size;
	int		index;
	void	*head;

	size = 0;
	index = 0;
	head = buflst;
	while (index <= is_nl(buflst))
	{
		if (ft_strchr(buflst->buf, '\n'))
			size += ft_strlen(buflst->buf)
				- ft_strlen(ft_strchr(buflst->buf, '\n'));
		else
			size += ft_strlen(buflst->buf);
		index++;
		buflst = buflst->next;
	}
	output = malloc(sizeof(char) * (size + 1));
	size = 0;
	buflst = head;
	while (buflst)
	{
		if (ft_strchr(buflst->buf, '\n'))
		{
			size += ft_strlen(buflst->buf)
				- ft_strlen(ft_strchr(buflst->buf, '\n'));
			ft_strlcat(output, buflst->buf, size);
		}
		else
		{
			size += ft_strlen(buflst->buf) + 1;
			ft_strlcat(output, buflst->buf, size);
		}
		buflst = buflst->next;
	}
	return (output);
}

char	*get_next_line(int fd)
{
	static t_buf	*buflst;
	char			output[BUFFER_SIZE + 1];
	int				byte_read;

	byte_read = read(fd, output, 10);
	if (byte_read <= 0)
		return (NULL);
	output[byte_read] = '\0';
	if (!buflst)
		buflst = ft_bufnew(output);
	else
	{
		buflst = bufclear(buflst);
		ft_bufadd_back(buflst, ft_bufnew(output));
	}
	if (is_nl(buflst))
	{
		return (extract_line(buflst));
	}
	while (byte_read > 0)
	{
		byte_read = read(fd, output, 10);
		output[byte_read] = '\0';
		ft_bufadd_back(buflst, ft_bufnew(output));
		if (is_nl(buflst))
		{
			return (extract_line(buflst));
		}
	}
	extract_line(buflst);
	return (buflst->buf);
}
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int	main(void)
{
	int		fd;
	int		i;
	char	*nl;

	fd = open("test", O_RDONLY);
	if (fd == -1)
		return (1);
	i = 0;
	nl = get_next_line(fd);
	nl = get_next_line(fd);
	nl = get_next_line(fd);
	nl = get_next_line(fd);
	while (nl[i])
	{
		write(1, &nl[i], 1);
		i++;
	}
	close(fd);
	return (0);
}
