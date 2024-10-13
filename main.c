/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hbreeze <hbreeze@student.42.fr>            #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024-10-13 16:56:54 by hbreeze           #+#    #+#             */
/*   Updated: 2024-10-13 16:56:54 by hbreeze          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dijkstra.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

int is_valid(void *map, t_position pos)
{
	t_dj_map *dj_map = (t_dj_map *)map;
	t_list *line = dj_map->map;
	while (pos.y && pos.y-- && line)
		line = line->next;
	if (!line || pos.y)
		return (0);
	return (((char *)line->content)[pos.x] != '#');
}

int get_type(void *map, t_position pos)
{
	t_dj_map *dj_map = (t_dj_map *)map;
	t_list *line = dj_map->map;
	while (pos.y && pos.y-- && line)
		line = line->next;
	if (!line || pos.y)
		return (0);
	return (((char *)line->content)[pos.x]);
}

int	main(int argc, char **argv)
{
	int fd;
	t_list *my_map;
	char *tmp;
	t_dj_map map;
	t_queue *queue = 0;

	if (argc != 2)
		return (1);
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		return (2);
	my_map = malloc(sizeof(t_list));
	if (!my_map)
		return (3);
	my_map->content = get_next_line(fd);
	my_map->next = 0;
	tmp = get_next_line(fd);
	while (tmp && *tmp != '\n')
	{
		ft_lstadd_back(&my_map, ft_lstnew(tmp));
		if (ft_strchr(tmp, 'P'))
			map.start = (t_position){ft_lstsize(my_map) - 1, ft_strchr(tmp, 'P') - tmp};
		tmp = get_next_line(fd);
	}
	if (tmp && *tmp == '\n')
		free(tmp);
	close(fd);
	
	map.width = ft_strlen(my_map->next->content) - 1;
	map.height = ft_lstsize(my_map);
	map.map = my_map;
	map.is_valid = is_valid;
	map.get_type = get_type;
	perform_dijkstra(&map);
	dijkstra_clean_up(map.cost_map, queue, &map);
	ft_lstclear(&my_map, &free);

	return (0);
}