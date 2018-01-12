/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Missile.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shedelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 13:28:19 by shedelin          #+#    #+#             */
/*   Updated: 2015/04/11 13:28:20 by shedelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MISSILE_HPP
# define MISSILE_HPP

# include <iostream>
# include "Entity.hpp"
# include "Player.hpp"
# include "Enemy.hpp"

class Enemy;

class Missile : public Entity {
protected:
	int			_damage;

public:
	
	Missile( void );
	Missile( std::string type, int X, int Y, int CHP, int MHP, bool CanShoot, int damage );
	Missile( Missile const & src );
	virtual ~Missile( void );
	
	int		getDam( void ) const;

	void		takeDamage( int const amount );
	void		move( int x, int y );
	void		die( void );
	Missile &	moveRight( void );
	void		moveLeft( void );
	void		Hit( Player & p );
	void		Hit( Enemy & e, Player & p );

	Missile & 		operator=(Missile const & rhs);
};

#endif

