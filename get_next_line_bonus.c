/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_redo.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleray <marvin@d42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:14:52 by jleray            #+#    #+#             */
/*   Updated: 2025/11/07 17:14:52 by jleray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*read_to_nl(char *left, int fd, int byte_read)
{
	char	*buf;
	char	*tmp;

	buf = ft_calloc(sizeof(char), (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	while (byte_read > 0)
	{
		byte_read = read(fd, buf, BUFFER_SIZE);
		if (byte_read < 0)
		{
			free(left);
			free(buf);
			return (NULL);
		}
		buf[byte_read] = '\0';
		tmp = ft_strjoin(left, buf);
		free(left);
		left = tmp;
		if (ft_strchr(left, '\n'))
			break ;
	}
	free(buf);
	return (left);
}

char	*extract_line(char *left)
{
	char	*output;
	size_t	len;

	if (!left)
		return (NULL);
	len = 0;
	while (left[len] && left[len] != '\n')
		len++;
	if (left[len] == '\n')
		len++;
	output = ft_substr(left, 0, len);
	return (output);
}

char	*clear_line(char *left)
{
	char	*new;
	size_t	i;

	if (!left)
		return (NULL);
	i = 0;
	while (left[i] && left[i] != '\n')
		i++;
	if (!left[i])
	{
		free(left);
		return (NULL);
	}
	new = ft_substr(left, i + 1, ft_strlen(left) - i);
	free(left);
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*left;
	char		*output;
	int			byte_read;

	if (fd == -1 || BUFFER_SIZE <= 0)
		return (0);
	if (!left)
		left = ft_calloc(sizeof(char), 1);
	if (!left)
		return (0);
	byte_read = 1;
	left = read_to_nl(left, fd, byte_read);
	if (!left)
		return (0);
	if (*left == '\0')
	{
		free(left);
		left = NULL;
		return (left);
	}
	output = extract_line(left);
	left = clear_line(left);
	return (output);
}
