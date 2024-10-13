/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print_dijkstra.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-13 10:28:17 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-13 10:28:17 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dijkstra.h"

#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

void debug_print_dijkstra( \
	t_cost_map cost_map,
	t_dj_map *map,
	t_position highlight,
	int	(*colour)(void *, t_position)
)
{
	size_t i;
	size_t j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (i == highlight.y && j == highlight.x)
				ft_putstr_fd(RED, 1);
			else
				ft_putstr_fd(((char *[]){WHITE, GREEN, YELLOW, BLUE, MAGENTA, CYAN, RED})[colour(map, (t_position){i,j})], 1);
			if (!map->is_valid(map, (t_position){i,j}))
				ft_putchar_fd('#', 1);
			else if (cost_map[i][j].cost == -1)
				ft_putchar_fd(' ', 1);
			else if (cost_map[i][j].cost < 10)
				ft_putchar_fd((char)(cost_map[i][j].cost + '0'), 1);
			else
				ft_putchar_fd((char)map->get_type(map, (t_position){i,j}), 1);
			ft_putstr_fd(" ", 1);
			ft_putstr_fd(RESET, 1);
			j++;
		}
		ft_putstr_fd("\n", 1);
		i++;
	}
}
