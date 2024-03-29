/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbartoul <sbartoul@student.42abudhabi.ae>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 22:17:03 by sbartoul          #+#    #+#             */
/*   Updated: 2024/01/28 19:45:20 by sbartoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	lentill_nline(char *bucket)
{
	int	i;

	i = 0;
	while (bucket[i] != '\n' && bucket[i])
		i++;
	if (bucket[i] == '\n')
		i++;
	return (i);
}

char	*after_nl(char *bucket)
{
	int		i;
	char	*part;

	i = lentill_nline(bucket);
	if (!bucket[i])
	{
		free(bucket);
		return (NULL);
	}
	part = ft_strdup(bucket + i);
	if (!part)
		return (NULL);
	free(bucket);
	return (part);
}

char	*fill_line(char *bucket)
{
	int		i;
	char	*line;

	i = lentill_nline(bucket);
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	line[i] = '\0';
	i = 0;
	while (bucket[i] && bucket[i] != '\n')
	{
		line[i] = bucket[i];
		i++;
	}
	if (bucket[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*readfrom_file(int fd, ssize_t *read_bytes, char *bucket, char *cup)
{
	char	*temp;

	while (!ft_strchr(bucket, '\n') && *read_bytes > 0)
	{
		*read_bytes = read(fd, cup, BUFFER_SIZE);
		if (*read_bytes <= 0)
		{
			free(cup);
			if (*read_bytes == 0)
				return (bucket);
			free(bucket);
			return (NULL);
		}
		cup[*read_bytes] = '\0';
		temp = bucket;
		bucket = ft_strjoin(bucket, cup);
		free(temp);
	}
	free(cup);
	return (bucket);
}

char	*get_next_line(int fd)
{
	static char	*bucket[OPEN_MAX];
	char		*line;
	char		*cup;
	ssize_t		read_bytes;

	if (fd < 0 || fd > OPEN_MAX || BUFFER_SIZE <= 0 || BUFFER_SIZE >= INT32_MAX)
		return (NULL);
	read_bytes = 1;
	cup = malloc(BUFFER_SIZE + 1);
	if (!cup)
		return (0);
	bucket[fd] = readfrom_file(fd, &read_bytes, bucket[fd], cup);
	if (!bucket[fd])
		return (NULL);
	line = fill_line(bucket[fd]);
	bucket[fd] = after_nl(bucket[fd]);
	return (line);
}
