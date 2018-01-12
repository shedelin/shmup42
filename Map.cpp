/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Map.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: birousse <birousse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/04/11 15:54:23 by birousse          #+#    #+#             */
/*   Updated: 2015/04/11 15:54:23 by birousse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Map.hpp"

std::string monsters[2] = {"monster", "asteroide"};

Map::Map(void): _width(0), _height(0), _time(0), _window(NULL), _J1(NULL), _J2(NULL)
{
	_Missile[0] = NULL;
	return ;
}

Map::Map(Map const &model) : _width(0), _height(0), _time(0), _window(NULL), _J1(NULL), _J2(NULL)
{
	*this = model;
	return ;
}

Map::~Map(void)
{
	return ;
}

Map&	Map::operator=(Map const &copy)
{
	*this = copy;
	return *this;
}

int 			Map::getWidth(void) const
{
	return (this->_width);
}

int 			Map::getHeight(void) const
{
	return (this->_height);
}

Player &		Map::getP1( void ) const {
	return *_J1;
}
Player &		Map::getP2( void ) const {
	return *_J2;
}

std::string		Map::getTime( void ) {
	std::stringstream	tmp;

	tmp << " " << (_time / 60) << ":" << (_time % 60);
	return tmp.str();
}

void			Map::setWidth(int width)
{
	this->_width = width;
	return ;
}

void			Map::setHeight(int height)
{
	this->_height = height;
	return ;
}

void		Map::initCurses(void)
{
	initscr();
	cbreak();
	nodelay(stdscr, TRUE);
	noecho();
	keypad(stdscr, TRUE);
	refresh();

	return ;
}

void		Map::initMap( int j)
{
	std::string			s2;
	std::stringstream	ss2;
	std::string			j1;
	std::stringstream	jj1;
	std::string			j2;
	std::stringstream	jj2;
	std::string			s1;
	std::stringstream	ss1;

	this->_window = newwin(this->_height, this->_width, 0, 0);
	box(this->_window, '|', '-');
	mvwhline(this->_window, 6, 0, '-', this->_width);	
	start_color();
	if (has_colors() == FALSE)
	{	endwin();
		printf("Your terminal does not support color\n");
		exit(1);
	}
	_J1 = new Player("#", POSX_P1, POSY_P1, 150, 150, true, 1);

	traceInfoP1( _J1->getX(), _J1->getY() );


	

	if ( j == 2 )
	{
		_J2 = new Player("@", POSX_P2, POSY_P2, 150, 150, true, 2);
		traceInfoP2( _J2->getX(), _J2->getY() );
	}
	setScroll();
	srand(time(NULL));
	for (int i = 0; i <= 105 ; i += 15) {
		createNewEnemy(345 - i, (rand() % 13) + 7, 40, "monster", 2, 500, 90, 90, 0);
		createNewEnemy(345 - i, (rand() % 13) + 20, 0, "asteroid", 15, 200, 240, 240, 1);
		createNewEnemy(345 - i, (rand() % 13) + 33, 40, "monster", 2, 500, 90, 90, 2);
	}
	wrefresh(this->_window);
	return ;
}

void			Map::refreshInfo( wchar_t c, int j ) {
	if (c == KEY_UP)
		_J1->moveUp();
	if (c == 10 || c == 13)
		_J1->shoot(*this);
	if (c == KEY_DOWN)
		_J1->moveDown(); // DOWN arrow
	if (j == 2)
	{
		if (c == 's')
			_J2->moveDown();
		if (c == 'w')
			_J2->moveUp();
		if (c == 32)
			_J2->shoot(*this);
	}

	static int			stime = 0;

	stime++;
	if (stime == 40)
	{
		_time += 1;
		stime = 0;
	}

	int		i;
	int		k;

	static int 			s_shoot = 0;
	int					l;

	s_shoot++;
	l = 0;
	while (l < 99)
	{
		if (_horde[l] != NULL)
		{
			if (s_shoot == 35)
			{
				_horde[l]->shoot(*this);
				if (l == 99)
					s_shoot = 0;
			}
		}
		l++;
	}

	static int 				s_enemy = 0;
	s_enemy++;

	if (s_enemy == 105)
	{
		int indX = 345;
		int indY = 0;
		while (indX >= 240)
		{
			indY = 7;
			while (indY < 47)
			{
				int indM = 0;
				while (indM < 99)
				{
					if (this->_horde[indM] != NULL && this->_horde[indM]->getX() == indX && 
						this->_horde[indM]->getY() == indY && !this->_horde[indM]->getState())
					{
						createNewEnemy(indX, (rand() % 13) + 7 + this->_horde[indM]->getSlot() * 13, 40,
						"monster", 2, 50, 90, 90, this->_horde[indM]->getSlot());
					}
					indM++;
				}
				indY++;
			}
			indX -= 15;
		}
		s_enemy = 0;
	}	

	i = 0;
	while (i < 399)
	{
		if (_Missile[i] != NULL )
		{
			if (_Missile[i]->getState()) 
			{
				if (_Missile[i]->getType() == "player")
				{
					k = 0;
					while (k < 99)
					{
						if (_horde[k] != NULL && _Missile[i] != NULL)
						{	

							if (_horde[k]->getX() == _Missile[i]->getX() && _horde[k]->getY() == _Missile[i]->getY())
							{
								_horde[k]->takeDamage( _Missile[i]->getDam(),  *_J1);
							}
						}
						k++;
					}
					if (k == 99)
						_Missile[i] = &_Missile[i]->moveRight();
				}
				else
				{
					if (_Missile[i] != NULL)
					{
						if (_J1->getX() == _Missile[i]->getX() && _J1->getY() == _Missile[i]->getY())
							_J1->takeDamage( _Missile[i]->getDam());
						else if ( j == 2 && (_J2->getX() == _Missile[i]->getX()) && (_J2->getY() == _Missile[i]->getY()))
							_J2->takeDamage( _Missile[i]->getDam());
						else
							_Missile[i]->moveLeft();
					}
				}
						
			}
			else
			{
				delete _Missile[i];
				_Missile[i] = NULL;
			}			
		}
		i++;
	}	
}

void		Map::refreshMap( int j )
{

	start_color();
	this->_window = newwin(this->_height, this->_width, 0, 0);
	box(this->_window, '|', '-');
	mvwhline(this->_window, 6, 0, '-', this->_width);
	traceInfoP1( _J1->getX(), _J1->getY() );

	if ( j == 2 )
		traceInfoP2( _J2->getX(), _J2->getY() );
	
	int		i;
	static	int		S_CShoot = 0;

	i = 0;
	S_CShoot++;
	while (i < 99)
	{
		if (_horde[i] != NULL)
		{	
			if ( _horde[i]->getState() && _horde[i]->getType() == "monster" )
			{
				std::string			e1;
				std::stringstream	ee1;

				ee1 << "#";
				e1 += ee1.str();
				char *	E1 = new char[e1.size() + 1];
				std::copy(e1.begin(), e1.end(), E1);
				E1[e1.size()] = '\0';
				traceEnemy(_horde[i]->getX(), _horde[i]->getY(), E1);
				if (S_CShoot == 35)
				{
					_horde[i]->shoot(*this);
				}
			}
			else if ( _horde[i]->getState() && _horde[i]->getType() == "asteroid" )
			{
				traceAsteroid(_horde[i]->getX(), _horde[i]->getY());
			}
		}
		i++;
	}
	if (S_CShoot > 35)
		S_CShoot = 0;

	i = 0;
	while (i < 399)
	{
		if (_Missile[i] != NULL)
		{
			if ( _Missile[i]->getState() && _Missile[i]->getType() == "player")
				traceMissileRight(_Missile[i]);
			else if ( _Missile[i]->getState() )
				traceMissileLeft(_Missile[i]);
		}
		i++;
	}
	setScroll();
	wrefresh(this->_window);
	return ;
}

void			Map::traceMissileRight( Missile * m) {
	if ( m->getState() ) {
		
		attron(COLOR_PAIR(1));
		mvprintw(m->getY(), m->getX(), "-");
		mvprintw(m->getY(), m->getX() - 1, " ");
		attroff(COLOR_PAIR(1));
	}
}

void			Map::traceMissileLeft( Missile * m) {
	if ( m->getState() ) {
		init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
		attron(COLOR_PAIR(3));
		mvprintw(m->getY(), m->getX(), "-");
		mvprintw(m->getY(), m->getX()  + 1, " ");
		attroff(COLOR_PAIR(3));
	}
}

void			Map::traceInfoP1( int x, int y )
{
	std::string			j1;
	std::stringstream	jj1;
	std::string			s1;
	std::stringstream	ss1;

	
	ss1 << "PLAYER 1                                " << _J1->getCHP() << "/" << _J1->getMHP() 
		<< " HP                                SHIELD : " << _J1->getCSH() << "                                ARMOR : " << _J1->getArm() 
		<< "                                WEAPON LVL : " 
		<< _J1->getWeapon() << "                                SCORE : " << _J1->getScore() 
		<< "                                TIME" << getTime();
	s1 += ss1.str();
	char *	c1 = new char[s1.size() + 1];
	std::copy(s1.begin(), s1.end(), c1);
	c1[s1.size()] = '\0';
	
	init_pair(1, COLOR_CYAN, COLOR_BLACK);	
	attron(COLOR_PAIR(1));
	mvprintw(HUD_P1Y, HUD_P1X, c1);
	if (_J1->getState()) {
		jj1 << _J1->getType();
		j1 += jj1.str();
		char *	J1 = new char[j1.size() + 1];
		std::copy(j1.begin(), j1.end(), J1);
		J1[j1.size()] = '\0';
		traceShip( y, x, J1 );
		attroff(COLOR_PAIR(1));
	}
}

void			Map::traceInfoP2( int x, int y )
{
	std::string			j2;
	std::stringstream	jj2;
	std::string			s2;
	std::stringstream	ss2;

	
		ss2 << "PLAYER 2                                " << _J2->getCHP() << "/" << _J2->getMHP() 
				<< " HP                                SHIELD : " << _J2->getCSH() << "                                ARMOR : " << _J2->getArm() 
				<< "                                WEAPON LVL : " 
				<< _J2->getWeapon(); 
		s2 += ss2.str();
		char *	c2 = new char[s2.size() + 1];
		std::copy(s2.begin(), s2.end(), c2);
		c2[s2.size()] = '\0';
		
		init_pair(2, COLOR_GREEN, COLOR_BLACK);
		attron(COLOR_PAIR(2));
		mvprintw(HUD_P2Y, HUD_P2X, c2);
		if (_J2->getState()) {
			jj2 << _J2->getType();
			j2 += jj2.str();
			char *	J2 = new char[j2.size() + 1];
			std::copy(j2.begin(), j2.end(), J2);
			J2[j2.size()] = '\0';
			traceShip(y, x, J2);
			attroff(COLOR_PAIR(2));
		}
}

void			Map::createNewMissile( int x, int y, int damage, std::string type ) {
	int		i;
	Missile*	new_m = new Missile(type, x, y, 1, 1, false, damage);
	i = 0;
	while (_Missile[i] != NULL && i < 399)
		i++;
	if (i >=399)
		return;
	_Missile[i] = new_m;
	_Missile[++i] = NULL;
}

void			Map::createNewEnemy(int x, int y, int damage, std::string type, int armor, int point, int chp, int mhp, int slot) {
	int i;
	Enemy*		new_e = new Enemy(type, x, y, chp, mhp, true, armor, damage, point, slot);
	bool		fire;

	fire = false;
	if ( damage > 0 )
		fire = true;

	i = 0;
	while (_horde[i] != NULL && i < 99)
		i++;
	if (i >= 99)
		return;
	_horde[i] = new_e;
	_horde[++i] = NULL;
}

void			Map::setScroll(void) {
	int pattern[20] = {0, 3, 0, 0, 2, 1, 0, 3, 4, 0, 0, 3, 0, 1, 0, 0, 0, 3, 1, 2};
	static int index = 0;
	int j;
	j = index;
	for (int i = 1; i < this->_width - 1; i++)
	{
		if (j == 20)
		        j = 0;
		mvwvline(this->_window, this->_height / 10 + 2, i, '*', pattern[j]);
		mvwvline(this->_window, (this->_height - 1) - pattern[j] , i, '*', pattern[j]);
		wrefresh(this->_window);
		j++;
	}
	(index == 20) ? index = 0 : index++;
}

void			Map::traceShip( int Y , int X, char *str ) {
	 mvprintw(Y, X, str);
	 mvprintw(Y, X - 1, str);
	 mvprintw(Y, X + 1, str);
	 
	 // up
	 if (Y > 7)
	 {
		 mvprintw(Y - 1, X, str);
		 mvprintw(Y - 1, X - 1, str);
		 mvprintw(Y - 1, X + 1, str);
	}

	 // down
	if (Y < HEIGHT - 3)
	{
		 mvprintw(Y + 1, X, str);
		 mvprintw(Y + 1, X + 1, str);
		 mvprintw(Y + 1, X - 1, str);
	}
}

void			Map::traceEnemy( int X , int Y, char *str ) {
	 mvprintw(Y, X, str);
	 mvprintw(Y, X - 1, str);
	 mvprintw(Y, X + 1, str);
	 
	 // up
	 if (Y > 7)
	 {
		mvprintw(Y - 1, X, str);
		mvprintw(Y - 1, X - 1, str);
		mvprintw(Y - 1, X + 1, str);
	}

	 // down
	if (Y < HEIGHT - 3)
	{
		mvprintw(Y + 1, X, str);
		mvprintw(Y + 1, X + 1, str);
		mvprintw(Y + 1, X - 1, str);
	}
}

void			Map::traceAsteroid( int X , int Y ) {
	 mvprintw(Y, X, " ");
	 mvprintw(Y, X - 1, "|");
	 mvprintw(Y, X + 1, "|");
	 
	 // up
	 if (Y > 7)
	 {
		mvprintw(Y - 1, X, " ");
		mvprintw(Y - 1, X - 1, "/");
		mvprintw(Y - 1, X + 1, "\\");
	}

	 // down
	if (Y < HEIGHT - 3)
	{
		mvprintw(Y + 1, X, " ");
		mvprintw(Y + 1, X + 1, "/");
		mvprintw(Y + 1, X - 1, "\\ ");
	}
}
