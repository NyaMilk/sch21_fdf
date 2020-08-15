/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jslave <jslave@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 19:04:56 by mgrass            #+#    #+#             */
/*   Updated: 2019/11/19 17:59:52 by jslave           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void		add_col_z1(int y, int x, t_bres *data, t_fdf *fdf)
{
	data->z_start = fdf->map[y][x] * fdf->step * fdf->resize;
	data->z_end = fdf->map[y + 1][x] * fdf->step * fdf->resize;
	data->color_st = fdf->color[y][x];
	data->color_end = fdf->color[y + 1][x];
}

void		add_col_z2(int y, int x, t_bres *data, t_fdf *fdf)
{
	data->z_start = fdf->map[y][x] * fdf->step * fdf->resize;
	data->z_end = fdf->map[y][x + 1] * fdf->step * fdf->resize;
	data->color_st = fdf->color[y][x];
	data->color_end = fdf->color[y][x + 1];
}

void		print_menu(t_fdf *lst)
{
	int		y;

	y = 0;
	mlx_string_put(lst->mlx_ptr, lst->win_ptr, 80, y += 50, 0x6F8F99,
		"HOW TO USE");
	mlx_string_put(lst->mlx_ptr, lst->win_ptr, 20, y += 30, 0xE5E5E5,
		"Change projection: Num5");
	mlx_string_put(lst->mlx_ptr, lst->win_ptr, 20, y += 30, 0xE5E5E5,
		"X_offset:  Right/Left");
	mlx_string_put(lst->mlx_ptr, lst->win_ptr, 20, y += 30, 0xE5E5E5,
		"Y_offset:  Up/Down");
	mlx_string_put(lst->mlx_ptr, lst->win_ptr, 20, y += 30, 0xE5E5E5,
		"Rotate X: Num6/Num4");
	mlx_string_put(lst->mlx_ptr, lst->win_ptr, 20, y += 30, 0xE5E5E5,
		"Rotate Y: Num8/Num2");
	mlx_string_put(lst->mlx_ptr, lst->win_ptr, 20, y += 30, 0xE5E5E5,
		"Resize: Num+/Num-");
	mlx_string_put(lst->mlx_ptr, lst->win_ptr, 20, y += 30, 0xE5E5E5,
		"Z-change: Num7/Num9");
	mlx_string_put(lst->mlx_ptr, lst->win_ptr, 20, y += 30, 0xE5E5E5,
		"Change colour: Num0");
	mlx_string_put(lst->mlx_ptr, lst->win_ptr, 20, y += 30, 0xE5E5E5,
		"Restore: Num*");
}
