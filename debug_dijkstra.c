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

int get_colour(void *map, t_position pos)
{
	t_dj_map *dj_map = (t_dj_map *)map;
	t_list *line = dj_map->map;
	while (pos.y && pos.y-- && line)
		line = line->next;
	if (!line || pos.y)
		return (0);
	if (((char *)line->content)[pos.x] == '#')
		return (4);
	if (((char *)line->content)[pos.x] == 'p')
		return (2);
	if (((char *)line->content)[pos.x] == 'C')
		return (3);
	if (((char *)line->content)[pos.x] == 'E')
		return (5);
	if (dj_map->cost_map[pos.y][pos.x].cost == -1)
		return (1);
	if (dj_map->cost_map[pos.y][pos.x].cost >= 0)
		return (6);
	return (1);
}

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
			{
				debug_print_dijkstra(cost_map, map, neighbour->pos, get_colour);
				dj_enqueue(queue, neighbour, cell->cost + 1);
			}
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
