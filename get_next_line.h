/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oaoba <oaoba@student.42tokyo.jp>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 21:01:30 by oaoba             #+#    #+#             */
/*   Updated: 2023/04/25 21:01:30 by oaoba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1122
# endif

typedef enum e_type{
	TYPE_READ_SUCCESS = 1,
	TYPE_EOF = 0,
	TYPE_READ_ERROR = -1,
}t_type;

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char *s1, char *s2);
char	*get_buffer(int fd, char *buffer);
char	*trim_over_from_buffer(char *buffer);
char	*trim_result_from_buffer(char *buffer);

#endif
