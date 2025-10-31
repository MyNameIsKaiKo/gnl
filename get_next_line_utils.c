/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleray <marvin@d42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:12:25 by jleray            #+#    #+#             */
/*   Updated: 2025/10/31 16:12:25 by jleray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		dst = 0;
		while (src[i])
			i++;
	}
	else
	{
		while (src[i] != '\0' && i < size - 1)
		{
			dst[i] = src[i];
			i++;
		}
		dst[i] = '\0';
		while (src[i])
			i++;
	}
	return (i);
}

t_buf	*ft_bufnew(char *content)
{
	t_buf	*output;

	output = malloc(sizeof(t_buf));
	if (!output)
		return (0);
	output->buf = malloc(sizeof(char) * (ft_strlen(content) + 1));
	ft_strlcpy(output->buf, content, ft_strlen(content) + 1);
	output->next = NULL;
	return (output);
}
