/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:12:26 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/13 16:40:18 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	put_pixel(t_cache *data, int x, int y, float z, int color)
{
	char	*dst;
	int		yy;
	int		xx;

	xx = (x - y) * cos(data->angle);
	yy = (x + y) * sin(data->angle);
	xx += data->x_offset;
	yy += data->y_offset;
	yy -= z;
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
	a->z *= data->zoom;
	b->x *= data->zoom;
	b->y *= data->zoom;
	b->z *= data->zoom;
}

void draw_line(t_point a, t_point b, t_cache *data)
{
    float x_step;
    float y_step;
    float z_step;
    int max;

    if (a.z != 0)
        a.z += data->altitude;
    if (b.z != 0)
        b.z += data->altitude;
    zoom(data, &a, &b);
    x_step = b.x - a.x;
    y_step = b.y - a.y;
    z_step = b.z - a.z;
    if (mod(x_step) > mod(y_step) && mod(x_step) > mod(z_step))
        max = mod(x_step);
    else if (mod(y_step) > mod(x_step) && mod(y_step) > mod(z_step))
        max = mod(y_step);
    else
        max = mod(z_step);
    x_step /= max;
    y_step /= max;
    z_step /= max;
    int color_a = 0xFFFFFF;
    int color_b = 0xaaaaaa;
    float r_step = ((color_b >> 16) & 0xFF - (color_a >> 16) & 0xFF) / (float)max;
    float g_step = ((color_b >> 8) & 0xFF - (color_a >> 8) & 0xFF) / (float)max;
    float b_step = ((color_b & 0xFF) - (color_a & 0xFF)) / (float)max;

    if (a.z != 0 && b.z == 0 && (a.z != 0 && b.z != 0))
    {
        int steps = 0;
        while ((int)(a.x - b.x) || (int)(a.y - b.y) || (int)(a.z - b.z))
        {
            int r = (int)((color_a >> 16) & 0xFF + (int)r_step * steps);
            int g = (int)((color_a >> 8) & 0xFF + (int)g_step * steps);
            int b = (int)(color_a & 0xFF + (int)b_step * steps);
            int color = (r << 16) | (g << 8) | b;

            put_pixel(data, a.x, a.y, a.z, color);
            a.x += x_step;
            a.y += y_step;
            a.z += z_step;
            steps++;
            if (a.y < 0 || a.x < 0)
                break ;
        }
    }
    else
    {
        int steps = 0;
        while ((int)(a.x - b.x) || (int)(a.y - b.y) || (int)(a.z - b.z))
        {
            int r = (int)((color_a >> 16) & 0xFF + (int)r_step * steps);
            int g = (int)((color_a >> 8) & 0xFF + (int)g_step * steps);
            int b = (int)(color_a & 0xFF + (int)b_step * steps);
            int color = (r << 16) | (g << 8) | b;

            put_pixel(data, a.x, a.y, a.z, color);
            a.x += x_step;
            a.y += y_step;
            a.z += z_step;
            steps++;
            if (a.y < 0 || a.x < 0)
                break ;
        }
    }
}

void print_menu(t_cache *data)
{
    char *menu;

    menu = "1: isometric/plane mode; ARROWS: move";
    if (mlx_string_put(data->mlx_ptr, data->win_ptr, 1600, 20, 0xffc589, menu) == 0)
        printf("Error: Unable to render menu 1\n");

    menu = "AD: Z-scale; NUMPAD +,-: zoom";
    if (mlx_string_put(data->mlx_ptr, data->win_ptr, 1600, 35, 0xffc589, menu) == 0)
        printf("Error: Unable to render menu 2\n");

    menu = "UO: z-rotation; IK: y-rotation; JL: x-rotation";
    if (mlx_string_put(data->mlx_ptr, data->win_ptr, 1600, 50, 0xffc589, menu) == 0)
        printf("Error: Unable to render menu 3\n");

    menu = "R: reset image, ESC: exit";
    if (mlx_string_put(data->mlx_ptr, data->win_ptr, 1600, 65, 0xffc589, menu) == 0)
        printf("Error: Unable to render menu 4\n");
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
	print_menu(data);
}
