/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-13 16:18:40 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-13 16:18:40 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "dijkstra.h"

static inline int clamp_int(int x, int min, int max)
{
	return (x * (x >= min && x < max) + min * (x < min) + max * (x >= max));
}

void	dijkstra(t_cost_map cost_map, t_queue **queue, t_dj_map *map)
{
	t_cell *cell;
	t_cell *neighbour;
	t_position neighbours[4];
	int i;

	neighbours[0] = (t_position){0, 1};
	neighbours[1] = (t_position){1, 0};
	neighbours[2] = (t_position){0, -1};
	neighbours[3] = (t_position){-1, 0};
	while ((cell = dj_dequeue(queue)))
	{
		i = 0;
		while (i < 4)
		{
			neighbour = &cost_map[ \
				clamp_int(cell->pos.y + neighbours[i].y, 0, map->height - 1) \
				][clamp_int(cell->pos.x + neighbours[i].x, 0, map->width - 1)];
			if (!neighbour->visited
				&& (neighbour->visited += 1)
				&&	map->is_valid(map, neighbour->pos))
				dj_enqueue(queue, neighbour, cell->cost + 1);
			i++;
		}
	}
}

int		perform_dijkstra(t_dj_map *map)
{
	t_queue *queue;

	if (!init_cost_map(map))
		return (0);
	queue = 0;
	map->cost_map[map->start.y][map->start.x].visited = 1;
	dj_enqueue(&queue, &map->cost_map[map->start.y][map->start.x], 0);
	dijkstra(map->cost_map, &queue, map);
	return (1);
}
