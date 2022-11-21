/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kben-ham <kben-ham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 15:14:04 by kben-ham          #+#    #+#             */
/*   Updated: 2022/11/19 17:08:10 by kben-ham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*ft_read_file(int fd, char **tmp)
{
	char		*p;
	int			nb;

	p = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!p)
		return (NULL);
	nb = 1;
	while (nb != 0 && ft_strchr(*tmp, '\n') == NULL)
	{
		nb = read(fd, p, BUFFER_SIZE);
		if (nb < 0)
		{
			free(p);
			free(*tmp);
			return (NULL);
		}
		p[nb] = '\0';
		*tmp = ft_strjoin(*tmp, p);
	}
	free(p);
	return (*tmp);
}

static char	*stop_line(char **tmp)
{
	int			i;
	char		*p1;
	char		*x;

	if (**tmp == 0)
		return (free(*tmp),*tmp = NULL, NULL);
	i = 0;
	if (ft_strchr(*tmp, '\n'))
	{
		while (tmp[0][i] != '\n' && tmp[0][i] != '\0')
			i++;
		if (tmp[0][i] == '\n')
			i++;
		p1 = malloc((i + 1));
		if (!p1)
			return (NULL);
		p1[i] = '\0';
		while (i--)
			p1[i] = tmp[0][i];
		x = *tmp;
		*tmp = ft_strdup(ft_strchr(*tmp, '\n') + 1);
		return (free(x), p1);
	}
	else
		return (p1 = ft_strdup(*tmp), free(*tmp), *tmp = NULL, p1);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*tmp[10240];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ft_read_file(fd, &tmp[fd]);
	if (tmp[fd] == NULL)
		return (NULL);
	line = stop_line(&tmp[fd]);
	return (line);
}

// int main ()
// {
// 	int fd = open("/dev/random", O_RDWR);
// // 	// printf("1 = %s\n",get_next_line(fd));
// // 	// printf("2 = %s\n",get_next_line(fd));
// // 	// printf("3 = %s\n",get_next_line(fd));
// // 	// printf("4 = %s\n",get_next_line(fd));
// // 	// printf("5 = %s\n",get_next_line(fd));
// // 	// printf("6 = %s\n",get_next_line(fd));
// // 	// printf("7 = %s\n",get_next_line(fd));
// 	char *line;
// 	line = get_next_line(fd);
// 	while(line)
// 	{
// 		printf("%s", line);
// 		free(line);
// 		line = get_next_line(fd);
// 	}
// // 	// while (1);
// }