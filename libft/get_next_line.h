/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/16 11:43:49 by agrodzin          #+#    #+#             */
/*   Updated: 2018/05/07 13:45:49 by agrodzin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define BUFF_SIZE 32

# include "libft.h"
# include <stdlib.h>
# include <unistd.h>

#define LINCHK(x) if (!x) return (0);

typedef struct      s_gnl
{
    int             fd;
    char            *storage;
    struct s_gnl    *next;
}                   t_gnl;

int		get_next_line(const int fd, char **line);

#endif
