#pragma once
#ifndef _STATES_H_
#define _STATES_H_

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <array>
#include <map>
#include "Button.h"
#include "Tile.h"
#include "Player.h"
#include "Label.h"

#define ROWS 24
#define COLS 32


class State // This is the abstract base class for all specific states.
{
public: // Public methods.
	virtual void Update() = 0; // Having at least one 'pure virtual' method like this, makes a class abtract.
	virtual void Render();     // Meaning we cannot create objects of the class.
	virtual void Enter() = 0;  // Virtual keyword means we can override in derived class.
	virtual void Exit() = 0;
	virtual void Resume();

protected: // Private but inherited.
	State() {}
};

class GameState : public State
{
private:
	SDL_Texture* m_pTileText, * m_pPlayerText;
	std::map<char, Tile*> m_tiles;
	std::array<std::array<Tile*, COLS>, ROWS> m_level; // Fixed-size STL array of Tile pointers.
	Player* m_pPlayer;
	Sprite* m_pBling;
	bool m_showCosts = false, m_hEuclid = true;

public:
	GameState();
	void Update();
	void Render();
	void Enter();
	void Exit();
	void Resume();
	std::array<std::array<Tile*, COLS>, ROWS> GetLevel() { return m_level; }
};

class TitleState : public State
{
public:
	TitleState();
	void Update();
	void Render();
	void Enter();
	void Exit();
private:
	Label* m_pName;
	Button* m_playBtn;
};



#endif