/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:07:29 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/11 21:10:10 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int		get_dots_from_line(char *line, t_point **dots, int y)
{
	char	**points;
	int		x;

	if (line)
		points = ft_split(line, ' ');
	else
		return (-1);
	x = 0;
	while (points[x])
	{
		dots[y][x].z = ft_atoi(points[x]);
		dots[y][x].x = x;
		dots[y][x].y = y;
		dots[y][x].is_last = 0;
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

void	free_structs(t_point **dots)
{
	int	i;
	
	i = 0;
	while (dots[i])
	{
		free(dots[i]);
		i++;
	}
	free(dots);
}

t_point	**memory_allocate(char *file_name, t_cache *data)
{
	t_point	**new;
	char	*line;
	int		i;
	int		height;
	
	if ((data->map_fd = open(file_name, O_RDONLY, 0)) <= 0)
		perror("Could not open map");
	get_next_line(data->map_fd, &line);
	get_measurements(line, data);
	free(line);
	while (get_next_line(data->map_fd, &line) > 0)
	{
		data->height++;
		free(line);
	}
	free(line);
	new = (t_point **)malloc(sizeof(t_point *) * (++data->height + 1));
	height = data->height;
	while (height > 0)
	{
		new[--height] = (t_point *)malloc(sizeof(t_point) * (data->width + 1));
		i = -1;
		while (++i < data->width)
			new[height][i].is_last = 1;
	}	
	close(data->map_fd);
	return (new);
}

void	read_map(char *file_name, t_cache *data)
{
	int		y;
	char	*line;

	data->dots = memory_allocate(file_name, data);

	data->map_fd = open(file_name, O_RDONLY, 0);
	y = 0;
	while (get_next_line(data->map_fd, &line) > 0)
		get_dots_from_line(line, data->dots, y++);
	free(line);
	data->dots[y] = NULL;
	close(data->map_fd);
}
