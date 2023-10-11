/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:12:26 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/11 19:04:12 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	iso(int x, int y, double angle)
{
	dot->x = (dot->x - dot->y) * cos(angle);
	dot->y = (dot->x + dot->y) * sin(angle) - dot->z;
}

void	put_pixel(t_cache *data, int x, int y, int color)
{
	char	*dst;
	int		xx;
	int		yy;
	
	xx = x;
	yy = y;
	x = (x - y) * cos(0.8);
	y = (x + y) * sin(0.8) ;
	dst = data->img.addr + ((int)y * data->img.l_l + (int)x * (data->img.bpp / 8));
	*(unsigned int*)dst = color;
}

void	draw_line(t_point a, t_point b, t_cache *data)
{
	float	x_step;
	float	y_step;
	int		max;

	// a.x *= 0.5;
	// a.y *= 0.5;
	// b.x *= 0.5;
	// b.y *= 0.5;
	x_step = b.x - a.x;
	y_step = b.y - a.y;	
	if (fabsf(x_step) > fabsf(y_step))
		max = fabsf(x_step);
	else
		max = fabsf(y_step);
	x_step /= max;
	y_step /= max;
	while ((int)(a.x - b.x) || (int)(a.y - b.y))
	{
		if (a.z <= 0)
			put_pixel(data, a.x, a.y, 0x3D34A2);
		else
			put_pixel(data, a.x, a.y, 0xFF0000);											
		a.x += x_step;
		a.y += y_step;
		if (a.y < 0 || a.x < 0)
			break;
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
		printf("%d\n", y);
	}
}