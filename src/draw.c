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
