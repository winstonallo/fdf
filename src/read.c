/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 11:07:29 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/11 20:46:26 by abied-ch         ###   ########.fr       */
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
void put_pixel(t_cache *data, int x, int y, int color)
{
    char *dst;
    float angle = 0.6; // Set your desired angle

    // Apply the isometric projection
    int xx = (x - y) * cos(angle);
    int yy = (x + y) * sin(angle);

    // Calculate the translation offsets
    // int x_center_offset = (1920 - 1) / 10;
    // int y_center_offset = (1080 - 1) / 10;

    // Apply the translation
    // xx += x_center_offset;
    // yy += y_center_offset;
	xx += 700;
    yy += 0;

    // Check if the transformed coordinates are within bounds
    if (xx >= 0 && xx < 1920 && yy >= 0 && yy < 1080) {
        dst = data->img.addr + ((int)yy * data->img.l_l + (int)xx * (data->img.bpp / 8));
        *(unsigned int *)dst = color;
    }
}





float mod(float i)
{
    if (i < 0)
        return -i;
	else 
        return i;
}

void	draw_line(t_point a, t_point b, t_cache *data)
{
	float	x_step;
	float	y_step;
	int		max;

	a.x *= 5;
	a.y *= 5;
	b.x *= 5;
	b.y *= 5;	// 
	x_step = b.x - a.x;
	y_step = b.y - a.y;	
	if (mod(x_step) > mod(y_step))
		max = mod(x_step);
	else
		max = mod(y_step);
	x_step /= max;
	y_step /= max;
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		if (a.z <= 0)
			put_pixel(data, a.x, a.y, 0xffffff);
		else if (a.z == 1)
			put_pixel(data, a.x, a.y, 0xFF0000);
		else if (a.z == 2)
			put_pixel(data, a.x, a.y, 0x1C8D30);
		else if (a.z == 3)
			put_pixel(data, a.x, a.y, 0x3D34A2);
		else if (a.z == 4)
			put_pixel(data, a.x, a.y, 0xD3F18E);
		else if (a.z == 5)
			put_pixel(data, a.x, a.y, 0x93D413);
		else if (a.z == 6)
			put_pixel(data, a.x, a.y, 0xB47A85);
		else if (a.z >= 7)
			put_pixel(data, a.x, a.y, 0xE87B06);
		else if (a.z >= 8)
			put_pixel(data, a.x, a.y, 0xFF0000);												
		a.x += x_step;
		a.y += y_step;
		if (a.y < 0 || a.x < 0)
			break;
	}
}

void	draw_grid(t_point **dots, t_cache *data)
{
	int	x;
	int	y;
	
	y = 0;
	while (y < data->height)
	{
		x = 0;
		while (x < data->width)
		{
			if (dots[y + 1])
			{
				draw_line(dots[y][x], dots[y + 1][x], data);
			}
			if (x < data->width - 1)
			{
				draw_line(dots[y][x], dots[y][x + 1], data);
			}
			x++;
		}
		y++;
	}
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
	draw_grid(data.dots, &data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img, 0, 0);
	mlx_hook(data.win_ptr, 2, 1L<<0, close_window, &data);
	mlx_loop(data.mlx_ptr);
	free_structs(data.dots);
}
