/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:12:26 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/11 23:00:29 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	ft_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < WIN_WIDTH && x > 0 && y < WIN_HEIGHT && y > 0)
	{
		dst = img->addr + (y * img->line_length + x
				* (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

void	ft_clear_map(t_vars *vars)
{
	vars->temp_y = 0;
	while (vars->temp_y < WIN_HEIGHT)
	{
		vars->temp_x = 0;
		while (vars->temp_x < WIN_WIDTH)
		{
			ft_mlx_pixel_put(vars->img, vars->temp_x, vars->temp_y, GREY);
			vars->temp_x++;
		}
		vars->temp_y++;
	}
	mlx_put_image_to_window(vars->mlx, vars->mlx_win, vars->img->img, 0, 0);
}

void	ft_draw_map(t_vars *vars)
{
	vars->temp_y = -1;
	while (++vars->temp_y < vars->map_height)
	{
		vars->temp_x = -1;
		while (++vars->temp_x < vars->map_width)
		{
			if (vars->temp_x < vars->map_width - 1)
			{
				vars->x1 = vars->temp_x;
				vars->y1 = vars->temp_y;
				vars->x2 = vars->temp_x + 1;
				vars->y2 = vars->temp_y;
				ft_draw_line(vars, vars->img);
			}
			if (vars->temp_y < vars->map_height - 1)
			{
				vars->x1 = vars->temp_x;
				vars->y1 = vars->temp_y;
				vars->x2 = vars->temp_x;
				vars->y2 = vars->temp_y + 1;
				ft_draw_line(vars, vars->img);
			}
		}
	}
}

void	ft_print_help(t_vars *vars)
{
	mlx_string_put(vars->mlx, vars->mlx_win, 10, 10, YELLOW,
		"translate: up down left right");
	mlx_string_put(vars->mlx, vars->mlx_win, 10, 30, YELLOW,
		"rotate: w s a d");
	mlx_string_put(vars->mlx, vars->mlx_win, 10, 50, YELLOW,
		"projection: 1 - 6");
	mlx_string_put(vars->mlx, vars->mlx_win, 10, 70, YELLOW,
		"altitude: [ ]");
	mlx_string_put(vars->mlx, vars->mlx_win, 10, 90, YELLOW,
		"zoom: < >");
	mlx_string_put(vars->mlx, vars->mlx_win, 10, 110, YELLOW,
		"color: c");
}

void	put_pixel(t_cache *data, int x, int y, int color)
{
	char	*dst;
	float	angle;
	int		yy;
	int		xx;

	angle = 0.55;
	xx = (x - y) * cos(angle);
	yy = (x + y) * sin(angle);
	xx += data->x_offset;
	yy += data->y_offset;
	if (xx >= 0 && xx < 1920 && yy >= 0 && yy < 1080)
	{
		dst = data->img.addr + ((int)yy * data->img.l_l
				+ (int)xx * (data->img.bpp / 8));
		*(unsigned int *)dst = color;
	}
}

float	mod(float i)
{
	if (i < 0)
		return (-i);
	else
		return (i);
}

void	zoom(t_cache *data, t_point *a, t_point *b)
{
	a->x *= data->zoom;
	a->y *= data->zoom;
	b->x *= data->zoom;
	b->y *= data->zoom;
}

void	draw_line(t_point a, t_point b, t_cache *data)
{
	float	x_step;
	float	y_step;
	int		max;

	zoom(data, &a, &b);
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
		else if (a.z > 0)
			put_pixel(data, a.x, a.y, 0xFF0000);
		a.x += x_step;
		a.y += y_step;
		if (a.y < 0 || a.x < 0)
			break ;
	}
}

void	draw(t_point **dots, t_cache *data)
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
