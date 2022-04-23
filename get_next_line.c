#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"


#include <stdio.h>

/**
 * Clean buffer and fill it reading from fd.
 * Return: numbers of bytes read or -1 if error
 */
int	ft_fill_buffer(char *buffer, int fd)
{
	int	bytes;
	int	i;

	ft_bzero(buffer, BUFFER_SIZE);
	bytes = 1;
	i = 0;
	while (bytes > 0 && i < BUFFER_SIZE - 1)
		bytes = read(fd, &buffer[i++], 1);
	if (bytes == -1)
		return (-1);
	buffer[i] = '\0';
	return (i - 1);
}

void	ft_clean_memory(char **memory)
{
	char	*new_memo;
	int		len;
	int		new_size;

	if (*memory == NULL)
	{
		*memory = (char *) malloc (sizeof(char));
		**memory = '\0';
		return ;
	}
	len = ft_line_len(*memory);
	new_size = ft_strlen(&(*memory)[len]) + 1;
	new_memo = (char *) malloc(sizeof(char) * new_size);
	ft_memcpy(new_memo, &(*memory)[len], new_size);
	free(*memory);
	*memory = new_memo;
}

int	fill_memory(char **memory, int fd)
{
	char	buffer[BUFFER_SIZE];
	int		ret;
	char	*tmp;

	ft_clean_memory(memory);
	while (!ft_strchr(*memory, '\n'))
	{
		ret = ft_fill_buffer(buffer, fd);
		if (ret < 1)
			return (ret);
		tmp = *memory;
		*memory = ft_strjoin(*memory, buffer);
		free(tmp);
	}
	return (ret);
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

char	*ft_get_line(char **memory)
{  
	char	*line;
	int		len;
	int		i;

	len = ft_line_len(*memory);
	if (len == 0)
		return (NULL);
	line = (char *) malloc(sizeof(char) * (len + 1));
	i = 0;
	while (i < len)
	{
		line[i] = (*memory)[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*memory = NULL;

	/*if (memory == NULL || *memory == '\0')*/
	if (fill_memory(&memory, fd) < 1)
		return (NULL);
	if (*memory == '\0')
		return (NULL);
//printf("memory: %s", memory);
	return (ft_get_line(&memory));
}
