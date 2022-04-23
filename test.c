#include <stdio.h>
#include <fcntl.h>
#include "get_next_line.h"

int	main(int ac, char **av)
{
	int 	fd = 0;
	char	*line;

	if (ac == 2)
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			puts("Cannot open file.");
			return (-1);
		}
	}
	line = get_next_line(fd);
/*printf("%s", line);*/
	/*line = get_next_line(fd);*/
/*printf("%s", line);*/
	while (line)
	{
		printf("%s", line);
		line = get_next_line(fd);
	}
}
