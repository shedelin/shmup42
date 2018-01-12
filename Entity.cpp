/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Entity.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shedelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 13:24:52 by shedelin          #+#    #+#             */
/*   Updated: 2015/04/11 13:24:54 by shedelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Entity.hpp"

Entity::Entity( void ) :
	_type("none"),
	_X(0),
	_Y(0),
	_CHP(0),
	_MHP(0),
	_CS(false),
	_state(true) {
}

Entity::Entity( std::string type, int X, int Y, int CHP, int MHP, bool CanShoot ) :
	_type(type),
	_X(X),
	_Y(Y),
	_CHP(CHP),
	_MHP(MHP),
	_CS(CanShoot)
{
	_state = true;
}

Entity::Entity( Entity const & src ) {
	*this = src;
}

Entity::~Entity( void ) {

}

std::string			Entity::getType( void ) const {
	return _type;
}

int					Entity::getX( void ) const {
	return _X;
}

int					Entity::getY( void ) const {
	return _Y;
}

int					Entity::getCHP( void ) const {
	return _CHP;
}

int					Entity::getMHP( void ) const {
	return _MHP;
}

bool				Entity::getCS( void ) const {
	return _CS;
}

bool				Entity::getState( void ) const {
	return _state;
}

void				Entity::takeDamage( int const amount ) {
	if (!_state)
		return;
	if ( (_CHP - amount)  <= 0 )
	{
		_CHP = 0;
		die();
	}
	else
		_CHP -= amount;
}

void				Entity::move( int x, int y ) {
	 if (!_state)
		return;
	 if ( x < 0 || y < 0 || x > WIDTH || y > HEIGHT )
	 	die();
	 else
	 {
	 	_X = x;
	 	_Y = y;
	 }
}

void				Entity::die( void ) {
	_CHP = 0;
	_state = false;
}

Entity &			Entity::operator=( Entity const & rhs ) {
	if ( this != &rhs)
	{
		_type = rhs.getType();
		_X = rhs.getX();
		_Y = rhs.getY();
		_CHP = rhs.getCHP();
		_MHP = rhs.getMHP();
		_CS = rhs.getCS();
		_state = rhs.getState();
	}
	return *this;
}
