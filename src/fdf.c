/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:14:44 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/12 17:42:13 by abied-ch         ###   ########.fr       */
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
	data->x_offset = 0;
	data->y_offset = 0;
	data->zoom = 10;
	data->angle = 0.6;
}

void	print_map(t_point **dots, t_cache *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->height)
	{
		j = 0;
		while (j < data->width)
		{
			printf("%3d", (int)dots[i][j].z);
			j++;
		}
		printf("\n");
		i++;
	}
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
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp,
			&data.img.l_l, &data.img.endian);
	draw(data.dots, &data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img, 0, 0);
	mlx_key_hook(data.win_ptr, do_shit, &data);
	mlx_loop(data.mlx_ptr);
	free_structs(data.dots);
}
