/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shedelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 13:25:52 by shedelin          #+#    #+#             */
/*   Updated: 2015/04/11 13:25:53 by shedelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Enemy.hpp"
#include "Player.hpp"

Enemy::Enemy( void ) : Entity() {
	_damage = 0;
	_armor = 0;
	_point = 0;
	_state = true;
}

Enemy::Enemy( std::string type, int X, int Y, int CHP, int MHP, bool CanShoot, int armor, int damage, int point, int slot ) : 
	Entity( type, X, Y, CHP, MHP, CanShoot ) {
	_damage = damage;
	_armor = armor;
	_point = point;
	_state = true;
	_slot = slot;
}

Enemy::Enemy( Enemy const & src ) : Entity( src ) {

}

Enemy::~Enemy( void ) {

}

int					Enemy::getArm( void ) const {
	return _armor;
}

int					Enemy::getDam( void ) const {
	return _damage;
}

int					Enemy::getPoint( void ) const {
	return _point;
}

int					Enemy::getSlot( void ) const {
	return _slot;
}

void				Enemy::shoot(Map & m) const {
	if (!_state || !_CS)
		return;
	m.createNewMissile((_X - 3), _Y, _damage, "enemy");
}

void				Enemy::takeDamage( int const amount, Player & p ) {
	if (!_state)
		return;
	if ( (_CHP - (amount - _armor)) <= 0 )
	{
		p.winPoint(_point);
		_CHP = 0;
		die();
	}
	else
		_CHP -= (amount - _armor);
}

void				Enemy::die( void ) {
	_state = false;
}

Enemy &			Enemy::operator=( Enemy const & rhs ) {
	if ( this != &rhs)
	{
		_type = rhs.getType();
		_X = rhs.getX();
		_Y = rhs.getY();
		_CHP = rhs.getCHP();
		_MHP = rhs.getMHP();
		_CS = rhs.getCS();
		_state = rhs.getState();
		_armor = rhs.getArm();
		_damage = rhs.getDam();
		_point = rhs.getPoint();
	}
	return *this;
}
