#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"


#include <stdio.h>

/**
 * Clean buffer and fill it reading from fd.
 * ptr points to beginning of buffer.
 * Return: numbers of bytes read
 */
int	fill_buffer(char *buffer, int fd, char **ptr)
{
	int	bytes;
	int	i;

	*ptr = buffer;
	bytes = 1;
	i = 0; // memset
	while (i < BUFFER_SIZE)
		buffer[i++] = '\0';
	i = 0;
	while (bytes > 0 && i < BUFFER_SIZE - 1)
		bytes = read(fd, &buffer[i++], 1);
	if (bytes == -1)
		return (-1);
	return (i);
}

int	ft_line_len(char *ptr)
{
	int	len;

	len = 0;
	while (ptr[len] && ptr[len] != '\n')
		len++;
	if (ptr[len] == '\n')
		len++;
	return (len);
}

char	*ft_get_line(char **ptr)
{
	char	*line;
	int		len;
	int		i;

	len = ft_line_len(*ptr);
	if (len == 0)
		return (NULL);
	line = (char *) malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		line[i] = (*ptr)[i];
		i++;
	}
	line[i] = '\0';
	*ptr = &(*ptr)[i];
	return (line);
}

char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE];
	static char	*ptr = NULL;

	if (ptr == NULL || ptr >= &buffer[BUFFER_SIZE])
		fill_buffer(buffer, fd, &ptr);
	if (ptr == NULL)
		return (NULL);
	return (ft_get_line(&ptr));
}
