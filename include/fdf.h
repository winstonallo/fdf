/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:43:04 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/11 10:31:00 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/include/libft.h"

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
	int	is_last;
}	t_point;

typedef struct s_image_data
{
	void	*img;
	char	*addr;
	int		bpp;
	int		l_l;
	int		endian;
}	t_image_data;

typedef struct s_cache
{
	char			**map;
	int				**int_map;
	int				width;
	int				height;
	int				height_as_well;
	int				map_fd;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	t_point			**dots;
	t_image_data	img;
	int				zoom;
}	t_cache;



int		main(int argc, char **argv);
void	free_array(char **arr);
void	empty_cache(t_cache *data);
int		find_coordinates(t_cache *data);
int		store_map(t_cache *data);
int		open_map(char *path, t_cache *data);
void	read_map(char *file_name, t_cache *data);

#endif