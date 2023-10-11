/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:07:29 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/11 21:02:46 by abied-ch         ###   ########.fr       */
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

void	initialize_cache(t_cache *data)
{
	data->map = NULL;
	data->map_fd = -1;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->height = 0;
	data->width = 0;
}


void print_map(t_point **dots, t_cache *data)
{
	int i = 0;
	int j;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			printf("%3d", dots[i][j].z);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	close_window(t_cache *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cache			data;

	if (argc != 2)
		return (ft_putendl_fd("Error: Invalid number of arguments", 2), -1);
	initialize_cache(&data);
	read_map(argv[1], &data);
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1920, 1080, "fdf");
	data.img.img = mlx_new_image(data.mlx_ptr, 1920, 1080);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp, &data.img.l_l, &data.img.endian);
	draw(data.dots, &data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img, 0, 0);
	mlx_hook(data.win_ptr, 2, 1L<<0, close_window, &data);
	mlx_loop(data.mlx_ptr);
	free_structs(data.dots);
}
