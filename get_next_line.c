/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:39:48 by yelu              #+#    #+#             */
/*   Updated: 2024/11/26 21:56:15 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*get_next_line(int fd)
{
	// read from a file
	// file descriptor
	// one line at a time
	int		bytes_read;
	char	*buff;
	static int count = 1;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	printf("ft_calloc#[%d]---", count++);
	buff = ft_calloc(3 + 1, sizeof(char));
	bytes_read = read(fd, buff, 3);
	if (bytes_read <= 0)
		return (free (buff), NULL);
	return (buff);
	
	
}
