/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_map2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/21 15:37:19 by yotsubo           #+#    #+#             */
/*   Updated: 2024/07/21 15:37:19 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

static t_point ***err_return(int *fd, char **input)
{
	if (fd)
		close(*fd);
	if (input)
		free_lines(input);
	return (NULL);
}

size_t	count_lines(char **lines)
{
	size_t	size;

	if (!lines)
		return (0);
	size = 0;
	while (lines[size])
		size++;
	return (size);
}

static char	**add_line(char **prev, char *line)
{
	size_t	prev_size;
	size_t	i;
	char	**res;

	prev_size = count_lines(prev);
	res = (char **)malloc(sizeof(char *) * (prev_size + 2));
	if (!res)
	{
		free_lines(prev);
		free(line);
		return (NULL);
	}
	i = 0;
	while (prev[i])
	{
		res[i] = prev[i];
		i++;
	}
	res[i++] = line;
	res[i] = NULL;
	free(prev);
	return (res);
}

static void	delete_nl(char *line)
{
	size_t	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			line[i] = '\0';
		i++;
	}
}

static char	**get_input(int fd)
{
	char	**res;
	char	*line;

	res = (char **)malloc(sizeof(char *));
	if (!res)
		return (NULL);
	res[0] = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		delete_nl(line);
		res = add_line(res, line);
		if (!res)
			return (NULL);
	}
	return (res);
}

static t_point	*init_point(int y, int x, int z)
{
	t_point	*point;

	point = (t_point *)malloc(sizeof(t_point));
	if (!point)
		return (NULL);
	point->x = x * 20 + 300;
	point->y = y * 20 + 200;
	point->z = z * 20;
	if (!z)
		point->color = 0x00FFFFFF;
	else
		point->color = 0x00FF0000;
	return (point);
}

static t_point	**line_convert_points(char *line, int x)
{
	t_point	**points;
	size_t	i;
	size_t	size;
	char	**elements;

	elements = ft_split(line, ' ');
	if (!elements)
		return (NULL);
	size = count_lines(elements);
	points = (t_point **)malloc(sizeof(t_point *) * (size + 1));
	if (!points)
	{
		free_lines(elements);
		return (NULL);
	}
	ft_bzero(points, sizeof(t_point *) * (size + 1));
	i = 0;
	while (i < size)
	{
		points[i] = init_point(x, (int)i, ft_atoi(elements[i]));
		if (!points[i])
		{
			free_points(points);
			free_lines(elements);
			return (NULL);
		}
		i++;
	}
	free_lines(elements);
	return (points);
}

static t_point	***get_map_data(char **input)
{
	t_point	***map;
	size_t	lines_size;
	size_t	i;

	lines_size = count_lines(input);
	map = (t_point ***)malloc(sizeof(t_point **) * (lines_size + 1));
	if (!map)
		return (NULL);
	ft_bzero(map, sizeof(t_point **) * (lines_size + 1));
	i = 0;
	while (input[i])
	{
		map[i] = line_convert_points(input[i], i);
		if (!map[i])
		{
			free_map(map);
			return (NULL);
		}
		i++;
	}
	return (map);
}

t_point	***make_map(char *filename)
{
	int		fd;
	char	**input;
	t_point	***map;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (err_return(NULL, NULL));
	input = get_input(fd);
	if (!input)
		return (err_return(&fd, NULL));
	map = get_map_data(input);
	if (!map)
		return (err_return(&fd, input));
	free_lines(input);
	close(fd);
	return (map);
}

// int	main(void)
// {
// 	t_point ***map;
//
// 	map = make_map("test_maps/mars.fdf");
// 	for (int i = 0; map[i]; i++)
// 	{
// 		for (int j = 0; map[i][j]; j++)
// 			printf("(%d, %d, %d) ", map[i][j]->x, map[i][j]->y, map[i][j]->z);
// 		puts("");
// 	}
// 	free_map(map);
// 	return (0);
// }