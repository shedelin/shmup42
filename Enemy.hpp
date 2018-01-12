/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Enemy.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shedelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 13:25:37 by shedelin          #+#    #+#             */
/*   Updated: 2015/04/11 13:25:44 by shedelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENEMY_HPP
# define ENEMY_HPP

# include <iostream>
# include "Entity.hpp"

class Player;
class Map;

class Enemy : public Entity {
protected:
	int			_armor;
	int			_damage;
	int			_point;
	int 		_slot;

public:
	
	Enemy( void );
	Enemy( std::string type, int X, int Y, int CHP, int MHP, bool CanShoot, int armor, int damage, int point, int slot);
	Enemy( Enemy const & src );
	virtual ~Enemy( void );

	int		getArm( void ) const ;
	int		getDam( void ) const ;
	int		getPoint( void ) const ;
	int 	getSlot( void ) const ;
	
	void	shoot(Map & m) const;
	void	takeDamage( int const amount, Player & p );
	void	die( void );

	Enemy & 		operator=(Enemy const & rhs);
};

#endif
