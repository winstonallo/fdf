/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:12:26 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/11 20:44:16 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void put_pixel(t_cache *data, int x, int y, int color)
{
    char *dst;
    float angle = 0.8; // Set your desired angle

    // Apply the isometric projection
    int xx = (x - y) * cos(angle);
    int yy = (x + y) * sin(angle);

    // Calculate the translation offsets
    // int x_center_offset = (1920 - 1) / 10;
    // int y_center_offset = (1080 - 1) / 10;

    // Apply the translation
    // xx += x_center_offset;
    // yy += y_center_offset;
	xx += 0;
    yy -= 0;

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

	// a.x *= 10;
	// a.y *= 10;
	// b.x *= 10;
	// b.y *= 10;	// 
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