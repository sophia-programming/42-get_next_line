/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaoba <oaoba@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 21:01:23 by oaoba             #+#    #+#             */
/*   Updated: 2023/04/25 21:01:23 by oaoba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_buffer(int fd, char *buffer)
{
	char	*storage;
	ssize_t	rd_bytes;

	storage = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (storage == NULL)
		return (NULL);
	rd_bytes = TYPE_READ_SUCCESS;
	while (ft_strchr(buffer, '\n') == NULL && rd_bytes != TYPE_EOF)
	{
		rd_bytes = read(fd, storage, BUFFER_SIZE);
		if (rd_bytes == TYPE_READ_ERROR)
		{
			free(storage);
			free(buffer);
			return (NULL);
		}
		storage[rd_bytes] = '\0';
		buffer = ft_strjoin(buffer, storage);
	}
	free(storage);
	return (buffer);
}

char	*trim_over_from_buffer(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*over_str;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	over_str = malloc(sizeof(char) * (ft_strlen(buffer) - i + 1));
	if (over_str == NULL)
	{
		free(buffer);
		return (NULL);
	}
	i++;
	j = 0;
	while (buffer[i])
		over_str[j++] = buffer[i++];
	over_str[j] = '\0';
	free(buffer);
	return (over_str);
}

char	*trim_result_from_buffer(char *buffer)
{
	size_t	i;
	char	*new;

	i = 0;
	if (buffer == NULL)
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	new = malloc(sizeof(char) * (i + 2));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		new[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		new[i] = buffer[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*get_next_line(int fd)
{
	static char	*over = NULL;
	char		*buffer;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = get_buffer(fd, over);
	if (buffer == NULL)
		return (NULL);
	result = trim_result_from_buffer(buffer);
	over = trim_over_from_buffer(buffer);
	if (result[0] == '\0' && over == NULL)
	{
		free(result);
		return (NULL);
	}
	else if (result[0] == '\0')
		free(result);
	return (result);
}


int main()
{
	int fd;
	fd = open("test.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file\n");
		return (1);
	}

	char *str;
	while ((str = get_next_line(fd)) != NULL)
	{
		printf("%s", str);
		free(str);
	}
	close(fd);
	return 0;
}
