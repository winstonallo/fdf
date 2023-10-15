/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abied-ch <abied-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 20:39:04 by abied-ch          #+#    #+#             */
/*   Updated: 2023/10/15 20:04:26 by abied-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	cleanup(t_cache *data)
{
	int	i;

	i = 0;
	if (data->dots)
	{
		while (i < data->height)
		{
			free(data->dots[i]);
			i++;
		}
	}
	free(data->dots);
}
