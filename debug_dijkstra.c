/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_dijkstra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-13 18:19:17 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-13 18:19:17 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dijkstra.h"
#include "dijkstra_debug.h"

int	get_colour(void *map, t_dj_position pos);

#ifndef DIJKSTRA_COLOURS
# define DIJKSTRA_COLOURS

int	get_colour(void *map, t_dj_position pos)
{
	t_dj_map	*dj_map;

	dj_map = (t_dj_map *)map;
	if (!dj_map->is_valid(dj_map, pos))
		return (2);
	if (dj_map->cost_map[pos.y][pos.x].cost == -1)
		return (4);
	if (pos.x == dj_map->start.x && pos.y == dj_map->start.y)
		return (5);
	return (1);
}
#endif

static inline int	clamp_int(int x, int min, int max)
{
	return (x * (x >= min && x < max)
		+ min * (x < min)
		+ max * (x >= max)
	);
}

static int	check_neighbors(t_cell *cell,
	t_dj_map *map,
	t_queue **queue,
	int dir[2]
)
{
	t_cell	*neighbour;

	if ((cell->pos.y == 0 && dir[0] == -1)
		|| cell->pos.y + dir[0] >= map->height
		|| (cell->pos.x == 0 && dir[1] == -1)
		|| cell->pos.x + dir[1] >= map->width)
		return (-1);
	neighbour = &map->cost_map
	[cell->pos.y + dir[0]]
	[cell->pos.x + dir[1]];
	if (!neighbour->visited && (++neighbour->visited)
		&& map->is_valid(map, neighbour->pos))
		dj_enqueue(queue, neighbour, cell->cost + 1);
	if (neighbour->cost > cell->cost + 1)
		neighbour->cost = cell->cost + 1;
	if (map->has_end
		&& neighbour->pos.y == map->end.y
		&& neighbour->pos.x == map->end.x)
		return (1);
	return (0);
}

void	dijkstra(t_queue **queue, t_dj_map *map)
{
	t_cell	*cell;
	int		dirs[4][2];

	dirs[0][0] = 0;
	dirs[0][1] = 1;
	dirs[1][0] = 1;
	dirs[1][1] = 0;
	dirs[2][0] = 0;
	dirs[2][1] = -1;
	dirs[3][0] = -1;
	dirs[3][1] = 0;
	cell = dj_dequeue(queue);
	while (cell)
	{
		usleep(PRINT_DELAY);
		debug_print_dijkstra(map, cell->pos, get_colour);
		if (check_neighbors(cell, map, queue, dirs[0]) == 1
			||check_neighbors(cell, map, queue, dirs[1]) == 1
			||check_neighbors(cell, map, queue, dirs[2]) == 1
			||check_neighbors(cell, map, queue, dirs[3]) == 1)
			return ;
		cell = dj_dequeue(queue);
	}
}

int	perform_dijkstra(t_dj_map *map)
{
	t_queue	*queue;

	if (!init_cost_map(map))
		return (0);
	queue = 0;
	map->cost_map[map->start.y][map->start.x].visited = 1;
	dj_enqueue(&queue, &map->cost_map[map->start.y][map->start.x], 0);
	dijkstra(&queue, map);
	ft_lstclear(&queue, free);
	return (1);
}
