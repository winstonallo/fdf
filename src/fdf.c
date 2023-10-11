/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 13:14:44 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/11 18:13:50 by abied-ch         ###   ########.fr       */
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
}

void	free_structs(t_point **dots)
{
	int	i;
	
	i = 0;
	while (dots[i])
	{
		free(dots[i]);
		i++;
	}
	free(dots);
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
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bpp, &data.img.l_l, &data.img.endian);
	draw(data.dots, &data);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.img, 1000, 500);
	mlx_hook(data.win_ptr, 2, 1L<<0, close_window, &data);
	mlx_loop(data.mlx_ptr);
	free_structs(data.dots);
}