#pragma once
#include <iostream>
#include "engine.h"
#include "titleScreen.hpp"
#include <bits/stdc++.h> 
#include <iomanip>
class TitleScene;

class MultiplayerScene : public Scene
{
private:

 	C2D_SpriteSheet dirtBg;
	C2D_Sprite dirtSpr;

 	C2D_SpriteSheet trollSheet;
 	C2D_SpriteSheet trollSheet2;
	std::array<C2D_Sprite,4> trollSprites;



	float scrollPos;



public:
 	
	MultiplayerScene()
	{

	}

	void load()
	{
		dirtBg = C2D_SpriteSheetLoad("romfs:/gfx/dirt-bg.t3x");
		trollSheet = C2D_SpriteSheetLoad("romfs:/gfx/trollface.t3x");
		trollSheet2 = C2D_SpriteSheetLoad("romfs:/gfx/trollface2.t3x");
	}

	void start()
	{
		C2D_SpriteFromSheet(&dirtSpr, dirtBg, 0);
		C2D_SpriteScale(&dirtSpr, 1, 1); 

		C2D_SpriteFromSheet(&trollSprites[0], trollSheet, 0);
		C2D_SpriteFromSheet(&trollSprites[1], trollSheet, 1);
		C2D_SpriteFromSheet(&trollSprites[2], trollSheet2, 0);
		C2D_SpriteFromSheet(&trollSprites[3], trollSheet2, 1);
	}

	void update()
	{
		float pAmount = Input::GetAxis(AnalogCode::PVertical);

		scrollPos += pAmount * 100 * Time::deltaTime;

		scrollPos = clamp(scrollPos, -3021, 0);

		for(int i = 0; i < static_cast<int>(trollSprites.size()); i++)
		{
			C2D_SpriteSetPos(&trollSprites[i], 0, scrollPos + (1000 *i));
		}		

		if(Input::GetKeyDown(KeyCode::B))
			SceneManagement::loadScene<TitleScene>();
	}

	void drawTop()
	{
		for(int i = 0; i < static_cast<int>(trollSprites.size()); i++)
			C2D_DrawSprite(&trollSprites[i]);

	}

	void drawBottom()
	{
		C2D_DrawSprite(&dirtSpr);
	}
	
	void unload()
	{
		C2D_SpriteSheetFree(dirtBg);
		C2D_SpriteSheetFree(trollSheet);
		C2D_SpriteSheetFree(trollSheet2);
	}

	~MultiplayerScene()
	{
		unload();
	}
};