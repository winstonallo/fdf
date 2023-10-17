/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:14:44 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/16 15:55:25 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	initialize_cache(t_cache *data)
{
	data->map = NULL;
	data->map_fd = -1;
	data->mlx_ptr = NULL;
	data->win_ptr = NULL;
	data->height = 0;
	data->width = 0;
	data->x_offset = 700;
	data->y_offset = 250;
	data->angle = 0.6;
	data->altitude = 0.5;
	data->zoom = 40;
	data->sea_level_color = 0xfbdddd;
	data->altitude_color = 0xbaf2ef;
}

int	close_window(t_cache *data)
{
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	clean(data->dots, data);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_cache			data;

	if (argc != 2)
		return (ft_putendl_fd("Error: Invalid number of arguments", 2), -1);
	initialize_cache(&data);
	if (read_map(argv[1], &data) == -1)
		return (-1);
	data.mlx_ptr = mlx_init();
	if (!data.mlx_ptr)
		return (perror("Malloc failed"), clean(data.dots, &data), -1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1920, 1080, "fdf");
	if (!data.win_ptr)
		return (perror("Malloc failed"), free(data.mlx_ptr),
			clean(data.dots, &data), -1);
	data.img.img = mlx_new_image(data.mlx_ptr, 1920, 1080);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp,
			&data.img.l_l, &data.img.endian);
	draw(data.dots, &data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img, 0, 0);
	print_menu(&data);
	mlx_key_hook(data.win_ptr, do_shit, &data);
	mlx_hook(data.win_ptr, 17, 0, close_window, &data);
	mlx_loop(data.mlx_ptr);
}
