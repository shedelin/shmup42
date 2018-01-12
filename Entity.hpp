/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shedelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 13:25:00 by shedelin          #+#    #+#             */
/*   Updated: 2015/04/11 13:25:02 by shedelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITY_HPP
# define ENTITY_HPP

# include <iostream>
# include "conf.hpp"

class Entity {

protected:
	std::string		_type;
	int				_X;
	int				_Y;
	int				_CHP;
	int				_MHP;
	bool			_CS;
	bool			_state;

public:
	
	Entity( void );
	Entity( std::string type, int X, int Y, int CHP, int MHP, bool CanShoot );
	Entity( Entity const & src );
	~Entity( void );

	std::string		getType( void ) const ;
	int				getX( void ) const;
	int				getY( void ) const;
	int				getCHP( void ) const;
	int				getMHP( void ) const;
	bool			getCS( void ) const;
	bool			getState( void ) const;

	void			takeDamage( int const amount );
	void			move( int x, int y );
	void			die( void );

	Entity & 		operator=(Entity const & rhs);
};

#endif
