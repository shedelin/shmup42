/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shedelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 13:31:09 by shedelin          #+#    #+#             */
/*   Updated: 2015/04/11 13:31:10 by shedelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Player.hpp"

Player::Player( void ) : Entity() {
	_armor = 0;
	_CSH = 0;
	_damage = 0;
	_Weapon = 0;
	_life = 0;
	_score = 0;
	_state = true;
	_index = 0;
}

Player::Player( std::string type, int X, int Y, int CHP, int MHP, bool CanShoot, int index ) : 
	Entity( type, X, Y, CHP, MHP, CanShoot ) {
	_armor = 5;
	_CSH = 0;
	_damage = DAM_P;
	_life = 3;
	_score = 0;
	_state = true;
	_index = index;
	if (_index == 1)
		_Weapon = 1;
	else
		_Weapon = 3;
}

Player::Player( Player const & src ) : Entity( src ) {

}

Player::~Player( void ) {

}

int					Player::getArm( void ) const {
	return _armor;
}

int					Player::getCSH( void ) const {
	return _CSH;
}

int					Player::getDam( void ) const {
	return _damage;
}

int					Player::getWeapon( void ) const {
	return _Weapon;
}

int					Player::getLife( void ) const {
	return _life;
}

int					Player::getScore( void ) const {
	return _score;
}

void				Player::shoot( void ) const {
	if (!_state || !_CS)
		return;
}

void				Player::takeDamage( int const amount ) {
	if (!_state)
		return;	
	if ( _CSH > 0 && _CSH - amount >= 0 )
	{
		_CSH -= amount;
		return;
	}
	if ( _CSH > 0 && _CSH - amount < 0 )
	{
		_CSH = 0;
		_CHP -= (amount - _CSH - _armor);
		if (_CSH < 0)
		{
			if (_life)
				lostLife();
			die();
		}
	}
	if ( (_CHP - (amount - _armor)) <= 0 )
	{
		_CHP = 0;
		if (_life)
			lostLife();
		die();
	}
	else
		_CHP -= (amount - _armor);
}

void				Player::moveDown( void ) {
	 if (!_state)
		return;
	 if ( (_Y + 1) > HEIGHT - 3 )
	 	die();
	 else
	 	_Y += 1;
}

void				Player::moveUp( void ) {
	 if (!_state)
		return;
	 if ( (_Y - 1) < 7 )
	 	die();
	 else
	 	_Y -= 1;
}

void				Player::lostLife( void ) {
	if (!_state)
		return;
	_CHP = _MHP;
	_CSH = 50;
	_damage = DAM_P;
	_Weapon = 1;
	_armor = 5;
	if (_index == 1)
		move( POSX_P1, POSY_P1 );
	if (_index == 2)
		move( POSX_P2, POSY_P2 );
}

void				Player::die( void ) {
	if (!_state)
		return;
	_CSH = 0;
	_CHP = 0;
	_state = false;
}

void				Player::shoot( Map & m ) const {
	if (!_state)
		return;
	if (_Weapon == 1)
		m.createNewMissile((_X + 3), _Y, _damage, "player");
	else if (_Weapon == 2)
	{
		m.createNewMissile((_X + 3), (_Y - 1), _damage, "player");
		m.createNewMissile((_X + 3), (_Y + 1), _damage, "player");
	}
	else
	{
		m.createNewMissile((_X + 3), (_Y - 1), _damage, "player");
		m.createNewMissile((_X + 3), _Y, _damage, "player");
		m.createNewMissile((_X + 3), (_Y + 1), _damage, "player");
	}
}

void				Player::winPoint( int const amount ) {
	if (!_state)
		return;
	static int		pointforlife = 1000;

	_score += amount;
	if (_score > pointforlife)
	{
		_life += 1;
		pointforlife += 1000;
	}
}

void				Player::armorUp( void ) {
	if (!_state)
		return;
	_armor += 5;
	if (_armor > MAX_ARM )
		_armor = MAX_ARM;
}

void				Player::shieldUp( void ) {
	if (!_state)
		return;
	_CSH += 50;
}

void				Player::HpUp( void ) {
	if (!_state)
		return;
	_CHP += 40;
	if (_CHP > _MHP)
		_CHP = _MHP;
}

void				Player::WeaponUp( void ) {
	if (!_state)
		return;
	_Weapon += 1;
	if ( _Weapon > 3 )
		_Weapon = 3;
}

Player &			Player::operator=( Player const & rhs ) {
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
	}
	return *this;
}

