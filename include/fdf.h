/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:43:04 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/12 18:25:34 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../libft/include/libft.h"

# define ESCAPE 65307
# define UP 65362
# define DOWN 65364
# define LEFT 65361
# define RIGHT 65363
# define ZOOM 65451
# define DEZOOM 65453
# define O 0x006F
# define U 0x0075
# define S 0x0073
# define W 0x0077

typedef struct s_point
{
	float	x;
	float	y;
	float	z;
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
	int				map_fd;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	t_point			**dots;
	t_image_data	new_img;
	t_image_data	img;
	int				zoom;
	int				x_offset;
	int				y_offset;
	float			angle;
	int				altitude;
}	t_cache;

int		main(int argc, char **argv);
void	free_array(char **arr);
void	empty_cache(t_cache *data);
int		find_coordinates(t_cache *data);
int		store_map(t_cache *data);
int		open_map(char *path, t_cache *data);
void	read_map(char *file_name, t_cache *data);
void	draw(t_point **dots, t_cache *data);
int		do_shit(int key, t_cache *data);
void	free_structs(t_point **dots);

#endif