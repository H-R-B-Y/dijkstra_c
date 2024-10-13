/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dijkstra.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-13 16:05:30 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-13 16:05:30 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIJKSTRA_H
# define DIJKSTRA_H

# include "./include/libft.h"

# include <stdlib.h>

# ifndef T_POSITION
#  define T_POSITION

typedef struct s_position
{
	size_t y;
	size_t x;
}	t_position;

# endif

typedef struct s_cell
{
	t_position pos;
	int cost;
	int visited;
} t_cell;

typedef t_list t_queue;
typedef t_cell **t_cost_map;

typedef struct s_dj_map
{
	size_t		width;
	size_t		height;
	void		*map;
	t_position	start;
	int 		has_end;
	t_position	end;
	int			(*is_valid)(void *, t_position);
	int			(*get_type)(void *, t_position);
	t_cost_map	cost_map;
} t_dj_map;

int		init_cost_map(t_dj_map *map);

void	dj_enqueue(t_queue **queue, t_cell *cell, int cost);

t_cell	*dj_dequeue(t_queue **queue);

void	dijkstra(t_cost_map cost_map, t_queue **queue, t_dj_map *map);

void	dijkstra_clean_up(t_cost_map cost_map, t_queue *queue, t_dj_map *map);

int		perform_dijkstra(t_dj_map *map);

void	debug_print_dijkstra( \
		t_cost_map cost_map,
		t_dj_map *map,
		t_position highlight,
		int	(*colour)(void *, t_position)
	);

#endif