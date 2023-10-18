/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:39:04 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/18 19:22:26 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	clean(t_point **dots, t_cache *data)
{
	int	i;

	i = 0;
	if (dots)
	{
		while (i < data->height)
		{
			free(dots[i]);
			i++;
		}
		free(dots);
	}
	close(data->map_fd);
}
