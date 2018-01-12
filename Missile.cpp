/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Missile.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shedelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 13:28:26 by shedelin          #+#    #+#             */
/*   Updated: 2015/04/11 13:28:28 by shedelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Missile.hpp"

Missile::Missile( void ) : Entity() {
	_state = true;
}

Missile::Missile( std::string type, int X, int Y, int CHP, int MHP, bool CanShoot, int damage ) : 
	Entity( type, X, Y, CHP, MHP, CanShoot ) {
	_damage = damage;
	_state = true;
}

Missile::Missile( Missile const & src ) : Entity( src ) {

}

Missile::~Missile( void ) {

}

int					Missile::getDam( void ) const {
	return _damage;
}

void				Missile::takeDamage( int const amount ) {
	(void)amount;
}

Missile &			Missile::moveRight( void ) {
	 if (!_state)
		return *this;
	 if (  _X > WIDTH - 2 )
	 	die();
	 else
	 	_X += 1;
	 return *this;
}

void				Missile::moveLeft( void ) {
	 if (!_state)
		return;
	 if (  _X < 1 )
	 	die();
	 else
	 	_X -= 1;
}

void				Missile::die( void ) {
	_state = false;
}

void				Missile::Hit( Player & p ) {
	p.takeDamage(_damage);
	die();
}

void				Missile::Hit( Enemy & e, Player & p ) {
	e.takeDamage(_damage, p);
	die();
}

Missile &			Missile::operator=( Missile const & rhs ) {
	if ( this != &rhs)
	{
		_type = rhs.getType();
		_X = rhs.getX();
		_Y = rhs.getY();
		_CHP = rhs.getCHP();
		_MHP = rhs.getMHP();
		_CS = rhs.getCS();
		_state = rhs.getState();
		_damage = rhs.getDam();
	}
	return *this;
}


