/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:39:04 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/16 13:31:43 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	cleanup(t_point **dots, t_cache *data)
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
}
