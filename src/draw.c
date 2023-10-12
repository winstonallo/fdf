/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:12:26 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/12 20:42:55 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

// t_point project_point(t_point p, t_cache *data)
// {
//     t_point result;
//     result.x = (p.x - p.y) * cos(data->angle) + data->x_offset;
//     result.y = (p.x + p.y) * sin(data->angle) + data->y_offset;
//     result.z = p.z; // Z coordinate remains the same after projection
//     return result;
// }

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

void	zoom2(t_cache *data, t_point *a)
{
	a->x *= data->zoom;
	a->y *= data->zoom;
	a->z *= data->zoom;
}

void	zoom3(t_cache *data, int *x, int *y, int *z)
{
	*x *= data->zoom;
	*y *= data->zoom;
	*z *= data->zoom;
}

void draw_point(int x, int y, int z, t_cache *data)
{
	zoom3(data, &x, &y, &z);
	z += data->altitude;
	if (z != 0)
        put_pixel(data, x, y, z, 0xFF0000);
}

void draw_line(t_point a, t_point b, t_cache *data)
{
    float x_step;
    float y_step;
	float z_step;
    int max;

    zoom(data, &a, &b);
    x_step = b.x - a.x;
    y_step = b.y - a.y;
	z_step = b.z - a.z;
    if (mod(x_step) > mod(y_step))
        max = mod(x_step);
    else
        max = mod(y_step);
    x_step /= max;
    y_step /= max;
	z_step /= max; 

    // Check if a and b have different altitudes and a is not at sea level
    if (a.z != 0 && b.z == 0 && (a.z != 0 && b.z != 0))
	{
        while ((int)(a.x - b.x) || (int)(a.y - b.y))
        {
            // if (a.z != 0)
            //     a.z += data->altitude;
            put_pixel(data, a.x, a.y, a.z, 0xFF0000);
            a.x += x_step;
            a.y += y_step;
			a.z += z_step;
            if (a.y < 0 || a.x < 0)
                break ;
        }
    }
        while ((int)(a.x - b.x) || (int)(a.y - b.y))
        {
            if (a.z != 0)
                a.z += data->altitude;
            put_pixel(data, a.x, a.y, a.z, 0xFF0000);
            a.x += x_step;
            a.y += y_step;
			a.z += z_step;
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
