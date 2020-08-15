/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgrass <mgrass@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 18:13:28 by jslave            #+#    #+#             */
/*   Updated: 2019/11/19 16:53:32 by mgrass           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int			main(int ac, char **av)
{
	t_fdf	*fdf;

	if (ac != 2)
	{
		ft_putendl("usage: ./fdf file");
		exit(1);
	}
	if (!(fdf = read_file(av[1])))
		error_out();
	create_map(fdf);
	draw_all(fdf);
	mlx_hook(fdf->win_ptr, 2, 0, key_press, fdf);
	mlx_loop(fdf->mlx_ptr);
	return (0);
}
