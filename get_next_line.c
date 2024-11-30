/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yelu <yelu@student.42kl.edu.my>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:39:48 by yelu              #+#    #+#             */
/*   Updated: 2024/11/30 15:12:49 by yelu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static char    *read_file(int fd, char *basin_buffer)
{
    int    bytes_read;
    char    *cup_buffer;
    char    *new_basin_buffer;

    cup_buffer = ft_calloc(1, BUFFER_SIZE + 1);
    if (!cup_buffer)
        return (NULL);
    bytes_read = 1;
    while (bytes_read != 0 && !ft_strchr(basin_buffer, '\n'))
    {
        bytes_read = read(fd, cup_buffer, BUFFER_SIZE);
        if (bytes_read == -1)
        {
            free(cup_buffer);
            free(basin_buffer);
            return (NULL);
        }
        cup_buffer[bytes_read] = '\0';
        new_basin_buffer = ft_strjoin(basin_buffer, cup_buffer);
        free(basin_buffer);
        basin_buffer = new_basin_buffer;
    }
    free(cup_buffer);
    return (basin_buffer);
}

static char *extract(char	*basin_buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (basin_buffer[i] == '\0')
		return (NULL);
	while (basin_buffer[i] != '\0' && basin_buffer[i] != '\n')
		i++;
	line = ft_substr(basin_buffer, 0, i + 1);
	if (line == NULL)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static char *update(char *basin_buffer)
{
	int	i;
	char	*line;
	
	if (basin_buffer == NULL)
		return (NULL);
	i = 0;
	while (basin_buffer[i] != '\n' && basin_buffer[i] != '\0')
	{
		i++;
	}
	if (basin_buffer[i] == '\0')
	{
		free(basin_buffer);
		return (NULL);
	}
	line = ft_substr(basin_buffer, i + 1, ft_strlen(basin_buffer) - i);
	if (line == NULL)
	{
		free(line);
		return (NULL);
	}
	free(basin_buffer);
	return (line);
}

char *get_next_line(int fd)
{
    static char    *basin_buffer;
    char    *line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!basin_buffer)
		basin_buffer = ft_strdup("");
    basin_buffer = read_file(fd, basin_buffer);
	if (!basin_buffer)
        return (NULL);
	line = extract(basin_buffer);
	basin_buffer = update(basin_buffer);
	return (line);
}

int main()
{
    char *line;
    int fd;

    fd = open("example.txt", O_RDONLY);
    if (fd == -1) {
        printf("Failed to open file or file does not exist");
        return (1);
    }
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("%s", line);
		free(line);
		line = get_next_line(fd);
	}
    close(fd);
    return (0);
}