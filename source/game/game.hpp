#pragma once
#include <iostream>
#include "engine.h"
#include "titleScreen.hpp"
#include <bits/stdc++.h> 
#include <iomanip>
class TitleScene;

class GameScene : public Scene
{
private:
	C2D_Font mcFont;
	C2D_SpriteSheet heartSSheet;
	std::array<C2D_Sprite,10> hearts;

public:
 	
	GameScene()
	{

	}

	void load()
	{
		mcFont = C2D_FontLoad("romfs:/mcfont.bcfnt");
		heartSSheet = C2D_SpriteSheetLoad("romfs:/gfx/hearts.t3x");

		//get width of all hearts minus from screen width /2 = offset 
	}

	void start()
	{
		for(int i = 0; i < static_cast<int>(hearts.size()); i++)
				C2D_SpriteFromSheet(&hearts[i], heartSSheet, 0);

	}

	void update()
	{

	}

	void drawTop()
	{

	}

	void drawBottom()
	{
		//for(int i = 0; i < static_cast<int>(hearts.size()); i++)
		//		C2D_DrawSprite(&hearts[i]);
	}	
	
	void unload()
	{
		
	}

	~GameScene()
	{
		unload();
	}
};