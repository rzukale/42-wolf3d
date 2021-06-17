/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rzukale <rzukale@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 12:27:40 by rzukale           #+#    #+#             */
/*   Updated: 2021/04/13 16:55:54 by rzukale          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	error_output(char *msg)
{
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}

void	usage(void)
{
	ft_putstr_fd("Usage: ./wolf3d <map-file>\n", 2);
	ft_putstr_fd("Use the arrow keys to move\n", 2);
	ft_putstr_fd("Press 'T' to switch projection mode\n", 2);
	ft_putstr_fd("Press 'U' to toggle shadows on/off\n", 2);
	ft_putstr_fd("Press 'M' to toggle minimap on/off\n", 2);
	ft_putstr_fd("Press 'ESC' or close window to quit\n", 2);
	ft_putstr_fd("Press 'F' to switch FPS cap (30 / 60)\n", 2);
	ft_putstr_fd("Press 'L' to unlock/lock FPS cap\n", 2);
}

int		main(int argc, char **argv)
{
	t_env env;

	if (argc == 2)
	{
		load_map(argv[1], &env.m);
		allocate_memory(&env);
		init_values(&env.p, &env.m);
		if (!init_sdl(&env))
			error_output("SDL failed to initialize!\n");
		else
			run_game(&env);
		free_all(&env);
		SDL_Quit();
	}
	else
		usage();
	return (EXIT_SUCCESS);
}
