/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:15:21 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/16 15:53:31 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	print_menu(t_cache *data)
{
	char	*menu;

	menu = "abied-ch's FDF:";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 20, 0xbcbcbc, menu);
	menu = "Press arrows to move the image";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 40, 0xbcbcbc, menu);
	menu = "Press O/U to tilt the picture";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 60, 0xbcbcbc, menu);
	menu = "Press W/S to change the altitude";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 80, 0xbcbcbc, menu);
	menu = "Press +/- (numpad) to zoom in/out";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 100, 0xbcbcbc, menu);
	menu = "Press SPACE to change the view (isometric/parallel)";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 120, 0xbcbcbc, menu);
	menu = "Press ESCAPE to exit";
	mlx_string_put(data->mlx_ptr, data->win_ptr, 20, 140, 0xbcbcbc, menu);
}

void	new_image(t_cache *data)
{
	if (data->img.img != NULL)
		mlx_destroy_image(data->mlx_ptr, data->img.img);
	data->img.img = mlx_new_image(data->mlx_ptr, 1920, 1080);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bpp, &data->img.l_l, &data->img.endian);
	draw(data->dots, data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	print_menu(data);
}

void	zoom(t_cache *data, t_point *a, t_point *b)
{
	if (data->zoom <= 0)
		data->zoom = 5;
	a->x *= data->zoom;
	a->y *= data->zoom;
	a->z *= data->zoom;
	b->x *= data->zoom;
	b->y *= data->zoom;
	b->z *= data->zoom;
}

void	do_shit2(int key, t_cache *data)
{
	if (key == ZOOM)
		data->zoom += 1;
	else if (key == DEZOOM)
		data->zoom -= 0.5;
	else if (key == O)
		data->angle += 0.1;
	else if (key == U)
		data->angle -= 0.1;
	else if (key == W)
		data->altitude *= 1.1;
	else if (key == S && (data->altitude > 0.09 || data->altitude < -0.09))
		data->altitude *= 0.9;
	else if (key == S && (data->altitude <= 0.09 && data->altitude > 0))
		data->altitude -= data->altitude + 0.1;
	else if (key == S && (data->altitude >= -0.09 && data->altitude < 0))
		data->altitude += 0.1;
	else if (key == SPACE)
	{
		if (data->angle == 0)
			data->angle = 0.6;
		else
			data->angle = 0;
	}
	new_image(data);
}

int	do_shit(int key, t_cache *data)
{
	if (key == ESCAPE)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.img);
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
		clean(data->dots, data);
		exit(0);
	}
	else if (key == RIGHT)
		data->x_offset += 100;
	else if (key == LEFT)
		data->x_offset -= 100;
	else if (key == UP)
		data->y_offset -= 100;
	else if (key == DOWN)
		data->y_offset += 100;
	else
		do_shit2(key, data);
	new_image(data);
	return (0);
}
