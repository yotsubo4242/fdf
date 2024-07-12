/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotsubo <y.otsubo.886@ms.saitama-u.ac.j    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 23:16:54 by yotsubo           #+#    #+#             */
/*   Updated: 2024/07/12 23:16:54 by yotsubo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf.h"
#include  "libft.h"

t_data	*err_return(t_data *data)
{
	if (data)
		free_data(data);
	return (NULL);
}

t_data	*data_init()
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(data));
	if (!data)
		return (err_return(NULL));
	ft_bzero(data, sizeof(data));
	data->mlx_ptr = mlx_init();
	if (!(data->mlx_ptr))
		return (err_return(data));
	data->win_ptr = mlx_new_window(data->mlx_ptr, 100, 100, "fdf");
	if (!(data->win_ptr))
		return (err_return(data));
	return (data);
}