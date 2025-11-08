/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jleray <marvin@d42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 09:51:22 by jleray            #+#    #+#             */
/*   Updated: 2025/11/07 09:51:22 by jleray           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != (char)c && s[i])
		i++;
	if (s[i] == (char)c)
		return ((char *)s + i);
	return (0);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	char	*alloc;
	size_t	i;

	if (nmemb == 0 || size == 0)
	{
		alloc = malloc(0);
		if (!alloc)
			return (0);
		return (alloc);
	}
	if (nmemb > (size_t)-1 / size)
		return (0);
	alloc = malloc(nmemb * size);
	if (!alloc)
		return (0);
	i = 0;
	while (i < (nmemb * size))
	{
		(alloc[i]) = 0;
		i++;
	}
	return (alloc);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	totallen;
	char	*output;
	size_t	i;
	size_t	len;

	if (!s1 || !s2)
		return (0);
	totallen = ft_strlen(s1) + ft_strlen(s2);
	output = ft_calloc(sizeof(char), (totallen + 1));
	if (output)
	{
		i = 0;
		len = ft_strlen(s1);
		while (*s1 && i < len)
			output[i++] = *s1++;
		while (*s2 && i < totallen)
			output[i++] = *s2++;
	}
	return (output);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*output;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	if (ft_strlen(s) <= start)
	{
		output = ft_calloc(sizeof(char), 1);
		return (output);
	}
	while (*(((char *)s) + start + i) != 0 && i < len)
		i++;
	output = ft_calloc(sizeof(char), (i + 1));
	if (!output)
		return (0);
	while (s + start + j && j < i)
	{
		output[j] = s[start + j];
		j++;
	}
	return (output);
}
