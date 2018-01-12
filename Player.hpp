/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Player.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shedelin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 13:31:15 by shedelin          #+#    #+#             */
/*   Updated: 2015/04/11 13:31:17 by shedelin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_HPP
# define PLAYER_HPP

# include <iostream>
# include "Entity.hpp"
# include "Map.hpp"
# include "Conf.hpp"

class Map;

class Player : public Entity {

protected:
	int			_armor;
	int			_CSH;
	int			_damage;
	int			_Weapon;
	int			_life;
	int			_score;
	int			_index;

public:
	
	Player( void );
	Player( std::string type, int X, int Y, int CHP, int MHP, bool CanShoot, int index );
	Player( Player const & src );
	virtual ~Player( void );
	
	int		getArm( void ) const;
	int		getCSH( void ) const;
	int		getDam( void ) const;
	int		getWeapon( void ) const;
	int		getLife( void ) const;
	int		getScore( void ) const;
	int		getIndex( void ) const;

	void	shoot( void ) const ;
	void	takeDamage( int const amount );
	void	moveUp( void );
	void	moveDown( void );
	void	lostLife( void );
	void	die( void );
	void	shoot( Map & m ) const ;
	void	winPoint( int const amount );
	void	armorUp( void );
	void	shieldUp( void );
	void	HpUp( void );
	void	WeaponUp( void );

	Player & 		operator=(Player const & rhs);
};

#endif
