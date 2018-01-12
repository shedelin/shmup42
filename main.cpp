/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: birousse <birousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 13:07:57 by birousse          #+#    #+#             */
/*   Updated: 2015/04/11 13:07:58 by birousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"

int		main( int ac, char **av ) 
{
	std::string		tmp;
	wchar_t			c;

	c = '\0';
	Map *map = new Map();
	if (ac > 1)
		tmp = av[1];
	map->initCurses();
	map->setWidth(WIDTH);
	map->setHeight(HEIGHT);
	if (tmp == "-p2")
		map->initMap(2);
	else
		map->initMap(1);
	
	while (42)
	{
		c = getch();
		if (c  == 27) // echap
			break;
		usleep(1000000 / 35);
		if (tmp == "-p2")
		{
			map->refreshInfo( c, 2 );
			map->refreshMap( 2 );
		}
		else
		{
			map->refreshInfo( c, 1 );
			map->refreshMap( 1 );
		}

	}
	endwin();
	return (0);
}		