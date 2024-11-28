/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fractol.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgoron <bgoron@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 21:46:02 by bgoron            #+#    #+#             */
/*   Updated: 2024/11/28 19:31:57 by bgoron           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_fract_ol.h"

int	main(int ac, char **av)
{
	t_fractol	*f;
	int			error;

	f = NULL;
	error = error_input(ac, av);
	if (!error)
	{
		init_fractol(ac, av, &f);
		print_fractal(f);
		mlx_on_event(f->mlx, f->win, 0, &key_hook, f);
		mlx_on_event(f->mlx, f->win, 2, &mouse_hook, f);
		mlx_on_event(f->mlx, f->win, 4, &wheel_hook, f);
		mlx_on_event(f->mlx, f->win, 5, &destroy, f);
		mlx_loop_hook(f->mlx, &loop_hook, f);
		mlx_loop(f->mlx);
	}
	return (0);
}
