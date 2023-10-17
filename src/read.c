/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:07:29 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/17 16:35:18 by abied-ch         ###   ########.fr       */
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
	int		in_number;
	size_t	i;

	i = 0;
	in_number = 0;
	while (line[i])
	{
		if (!space(line[i]) && !in_number)
		{
			in_number = 1;
			data->width++;
		}
		else if (space(line[i]))
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
			return (clean(new, data), NULL);
	}
	return (new);
}

t_point	**make_room(char *file_name, t_cache *data)
{
	t_point	**new;
	char	*line;

	data->map_fd = open(file_name, O_RDONLY, 0);
	if (data->map_fd <= 0)
		return (perror("Could not open map"), NULL);
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
	if (close(data->map_fd) == -1)
		return (clean(new, data), NULL);
	return (new);
}

int	read_map(char *file_name, t_cache *d)
{
	int		y;
	char	*line;

	d->dots = make_room(file_name, d);
	if (!d->dots)
		exit(EXIT_FAILURE);
	d->map_fd = open(file_name, O_RDONLY, 0);
	if (d->map_fd == -1)
		return (perror("Could not open map"), clean(d->dots, d), -1);
	y = 0;
	while (get_next_line(d->map_fd, &line) > 0)
	{
		if (!line)
			return (perror("Memory allocation failed"), clean(d->dots, d), -1);
		if (check_line_length(line, d) == -1)
			return (ft_putendl_fd("Invalid Map: Line length not constant", 2),
				free(line), clean(d->dots, d), -1);
		if (get_dots_from_line(line, d->dots, y++) != d->width)
			return (perror("Memory allocation failed"), clean(d->dots, d), -1);
	}
	free(line);
	d->dots[y] = NULL;
	if (close(d->map_fd) == -1)
		return (clean(d->dots, d), -1);
	return (0);
}
