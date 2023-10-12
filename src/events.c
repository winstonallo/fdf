/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:15:21 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/12 21:17:32 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	new_image(t_cache *data)
{
	data->img.img = mlx_new_image(data->mlx_ptr, 1920, 1080);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bpp,
			&data->img.l_l, &data->img.endian);
	draw(data->dots, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}

int	do_shit2(int key, t_cache *data)
{
	if (key == ZOOM)
	{
		data->zoom += 1;
		new_image(data);
	}
	if (key == DEZOOM)
	{
		data->zoom -= 0.5;
		new_image(data);
	}
	if (key == DOWN)
	{
		data->y_offset += 20;
		new_image(data);
	}
	if (key == 0x006F)
	{
		data->angle += 0.1;
		new_image(data);
	}
	if (key == 0x0075)
	{
		data->angle -= 0.1;
		new_image(data);
	}
	if (key == 0x0077)
	{
		data->altitude -= 1;
		new_image(data);
	}
	if (key == 0x0073)
	{
		data->altitude += 1;
		new_image(data);
	}
	return (0);
}

int	do_shit(int key, t_cache *data)
{
	if (key == ESCAPE)
	{
		mlx_destroy_display(data->mlx_ptr);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);		
		free(data->mlx_ptr);
		free_structs(data->dots);
		
		exit(0);
	}
	if (key == RIGHT)
	{
		data->x_offset += 20;
		new_image(data);
	}
	if (key == LEFT)
	{
		data->x_offset -= 20;
		new_image(data);
	}
	if (key == UP)
	{
		data->y_offset -= 20;
		new_image(data);
	}
	else
		do_shit2(key, data);
	return (0);
}
