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



char	*get_next_line(int fd)
{
}

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int	main(void)
{
	int	fd;

	fd = open("test", O_RDONLY);
	if (fd == -1)
		return (1);
	int i = 0;
	char *nl = get_next_line(fd);
	while (nl[i])
	{
		write(1, &nl[i], 1);
		i++;
	}
	close(fd);
	return (0);
}
