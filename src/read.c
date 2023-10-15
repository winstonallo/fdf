/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:07:29 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/15 20:11:10 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	get_dots_from_line(char *line, t_point **dots, int y)
{
	char	**points;
	int		x;

	if (line)
	{
		points = ft_split(line, ' ');
		if (!points)
			return (free(line), -1);
	}
	else
		return (-1);
	x = 0;
	while (points[x])
	{
		dots[y][x].z = ft_atoi(points[x]);
		if (abs(dots[y][x].z > 15))
			dots[y][x].z = 15;
		dots[y][x].x = x;
		dots[y][x].y = y;
		free(points[x++]);
	}
	free(points);
	free(line);
	return (x);
}

void	get_measurements(char *line, t_cache *data)
{
	int	in_number;
	int	i;

	i = 0;
	in_number = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]) && !in_number)
		{
			in_number = 1;
			data->width++;
		}
		else
			in_number = 0;
		i++;
	}
}

t_point	**allocate(t_cache *data)
{
	t_point	**new;
	int		height;

	new = (t_point **)malloc(sizeof(t_point *) * (++data->height + 1));
	if (!new)
		return (NULL);
	height = data->height;
	while (height > 0)
	{
		new[--height] = (t_point *)malloc(sizeof(t_point) * (data->width + 1));
		if (!new[height])
			return (cleanup(data), NULL);
	}
	return (new);
}

t_point	**make_room(char *file_name, t_cache *data)
{
	t_point	**new;
	char	*line;

	data->map_fd = open(file_name, O_RDONLY, 0);
	if (data->map_fd <= 0)
		perror("Could not open map");
	if (get_next_line(data->map_fd, &line) == -1)
		return (NULL);
	get_measurements(line, data);
	free(line);
	while (get_next_line(data->map_fd, &line) > 0)
	{
		data->height++;
		free(line);
	}
	if (!line)
		return (NULL);
	free(line);
	data->zoom -= data->height;
	new = allocate(data);
	if (!new)
		return (NULL);
	close(data->map_fd);
	return (new);
}

int	read_map(char *file_name, t_cache *data)
{
	int		y;
	char	*line;

	data->dots = make_room(file_name, data);
	if (!data->dots)
		exit(EXIT_FAILURE);
	data->map_fd = open(file_name, O_RDONLY, 0);
	if (data->map_fd == -1)
		return (perror("Could not open map"), -1);
	y = 0;
	while (get_next_line(data->map_fd, &line) > 0)
	{
		if (!line)
			return (perror("Memory allocation failed"), cleanup(data), -1);
		if (check_line_length(line, data) == -1)
			return (ft_putendl_fd("Invalid Map: Line length not constant", 2),
				free(line), cleanup(data), -1);
		if (get_dots_from_line(line, data->dots, y++) == -1)
			return (perror("Memory allocation failed"), cleanup(data), -1);
	}
	free(line);
	data->dots[y] = NULL;
	close(data->map_fd);
	return (0);
}
