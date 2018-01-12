/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: birousse <birousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 15:54:15 by birousse          #+#    #+#             */
/*   Updated: 2015/04/11 15:54:16 by birousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP

# include <string>
# include <iostream>
# include <sstream>
# include <ncurses.h>
# include <curses.h>
# include <ctime>
# include <stdlib.h>
# include <unistd.h>
# include <list>
# include "Player.hpp"
# include "Conf.hpp"
# include "Missile.hpp"
# include "Enemy.hpp"

class Player;
class Missile;

class Map
{
	public:
		Map( void );
		Map( Map const & src );
		virtual ~Map( void ) ;

		Map&			operator=( Map const & rhs );

		int 			getWidth(void) const ;
		int 			getHeight(void) const ;
		Player &		getP1( void ) const ;
		Player &		getP2( void ) const ;
		std::string 	getTime( void ) ;

		void			setWidth(int width);
		void			setHeight(int height);
		void			initCurses(void);
		void			initMap(int j);
		void			refreshMap( int j );
		void			refreshInfo( wchar_t c, int j );

		void			createNewMissile( int x, int y, int damage, std::string type );
		void			createNewEnemy(int x, int y, int damage, std::string type, int armor, int point, int chp, int mhp, int slot);
		void			traceShip( int Y , int X, char *str );
		void			traceInfoP1( int x, int y );
		void			traceMissileRight( Missile * m);
		void			traceMissileLeft( Missile * m);
		void			traceInfoP2( int x, int y );
		void			traceAsteroid( int X , int Y );
		void			traceEnemy( int x, int y, char *str );
		void			setScroll(void);

	private:
		int 					_width;
		int 					_height;
		Enemy *					_horde[100];
		int 					_time;
		WINDOW*					_window;
		Player*					_J1;
		Player*					_J2;
		Missile *				_Missile[400];
};

std::ostream	&operator<<( std::ostream &o, Map const & i);

#endif