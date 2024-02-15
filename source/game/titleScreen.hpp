#pragma once
#include <iostream>
#include "engine.h"
#include "button.hpp"
#include "multiplayerScene.hpp"
#include "game.hpp"
#include "label.hpp"

class TitleScene : public Scene
{
private:
	int currFrame = 0;
	const int maxFrames = 1;

 	C2D_SpriteSheet bgSprites;
 	C2D_SpriteSheet mcLogo;
 	C2D_SpriteSheet dirtBg;
 	C2D_SpriteSheet buttonSprSh;

	C2D_Sprite bgSpr;
	C2D_Sprite mcLogoSpr;
	C2D_Sprite dirtSpr;

	C2D_Font mcFont;

	std::array<Button, 3> btns;

	int selectedButton = 0;

	Label creds;

public:
 	
	TitleScene()
	{

	}

	void load()
	{
		bgSprites = C2D_SpriteSheetLoad("romfs:/gfx/bg.t3x");
		mcLogo = C2D_SpriteSheetLoad("romfs:/gfx/logo.t3x");
		dirtBg = C2D_SpriteSheetLoad("romfs:/gfx/dirt-bg.t3x");
		buttonSprSh = C2D_SpriteSheetLoad("romfs:/gfx/button.t3x");

		mcFont = C2D_FontLoad("romfs:/mcfont.bcfnt");
	}

	void start()
	{
		C2D_SpriteFromSheet(&mcLogoSpr, mcLogo, 0);
		C2D_SpriteScale(&mcLogoSpr, 1, 1); 
		C2D_SpriteSetCenter(&mcLogoSpr, 0.5f, 0.5f);
		C2D_SpriteSetPos(&mcLogoSpr,TOP_SCREEN_WIDTH/2, TOP_SCREEN_HEIGHT/2);

		C2D_SpriteFromSheet(&dirtSpr, dirtBg, 0);
		C2D_SpriteScale(&dirtSpr, 1, 1); 
	
		float spacing = 20;


		btns[0] = Button(&buttonSprSh, "Singleplayer", &mcFont, C2D_Color32f(1.0f, 1.0f, 1.0f, 1.0f), BOTTOM_SCREEN_WIDTH /2, 24, .35, .5f);		
		btns[1] = Button(&buttonSprSh, "Dungeons", &mcFont, C2D_Color32f(1.0f, 1.0f, 1.0f, 1.0f), BOTTOM_SCREEN_WIDTH /2, (24*2) +spacing, .35, .5f);
		btns[2] = Button(&buttonSprSh, "Multiplayer", &mcFont, C2D_Color32f(1.0f, 1.0f, 1.0f, 1.0f), BOTTOM_SCREEN_WIDTH /2, (24 * 3.85f) +spacing, .35, .5f);
		btns[selectedButton].changedSelected(1);

		creds = Label("Game created by DogeDoge 2021 || Orignal Game By Mojang", &mcFont, C2D_Color32f(1.0f, 1.0f, 1.0f, 1.0f), 0, TOP_SCREEN_HEIGHT - 16, .4f, .4f);
	}

	void update()
	{
		if(currFrame == 1)
			currFrame = 0;
		else if(currFrame == 0)
			currFrame = 1;

		C2D_SpriteFromSheet(&bgSpr, bgSprites, currFrame);
		C2D_SpriteScale(&bgSpr, .666, .5325); 

		bool change = false;
		if(Input::GetKeyDown(KeyCode::Down)){
			selectedButton++;
			if(selectedButton > static_cast<int>(btns.size())-1)
				selectedButton = 0;
			change = true;
		}
		if(Input::GetKeyDown(KeyCode::Up))
		{
			selectedButton--;
			if(selectedButton < 0)
				selectedButton = static_cast<int>(btns.size())-1;
			change = true;
		}

		if(change)
		{
			for(int i = 0; i < static_cast<int>(btns.size());  i++)
			{
				btns[i].changedSelected(0);
			}

			btns[selectedButton].changedSelected(1);
		}

		if(Input::GetKeyDown(KeyCode::A))
		{
			switch(selectedButton)
			{
				case 0:
						SceneManagement::loadScene<GameScene>();
					break;
				case 1:
						SceneManagement::loadScene<GameScene>();
					break;
				case 2:						
					SceneManagement::loadScene<MultiplayerScene>();
					break;				
			}
		}

		for(int i = 0; i < static_cast<int>(btns.size()); i++)
		{
			if(btns[i].checkPressed())
			{

				for(int j = 0; j < static_cast<int>(btns.size());  j++)
				{
					btns[j].changedSelected(0);
				}	

				btns[i].changedSelected(1);
				selectedButton = i;
				switch(i)
				{
					case 0:
						SceneManagement::loadScene<GameScene>();
						break;
					case 1:
						SceneManagement::loadScene<GameScene>();
						break;
					case 2:						
						SceneManagement::loadScene<MultiplayerScene>();
						break;				
				}
			}
		}

		if(Input::GetKeyDown(KeyCode::X))
		{
			SceneManagement::loadScene<TitleScene>();
		}
		
		
	}

	void drawTop()
	{
		C2D_DrawSprite(&bgSpr);
		C2D_DrawSprite(&mcLogoSpr);
		creds.render();
	}

	void drawBottom()
	{
		C2D_DrawSprite(&dirtSpr);
		
		for(auto el : btns){
			el.render();
		}

		/*btns[0].render();
		btns[1].render();
		btns[2].render();*/
		//C2D_DrawRectangle (0, 0, 0, BOTTOM_SCREEN_WIDTH/2, BOTTOM_SCREEN_HEIGHT/2, C2D_Color32f(0.0f, 1.0f, 1.0f, 1.0f), C2D_Color32f(1.0f, 0.0f, 1.0f, 1.0f), C2D_Color32f(1.0f, 1.0f, 1.0f, 1.0f), C2D_Color32f(1.0f, 1.0f, 1.0f, 1.0f));
	}
	
	void unload()
	{
		C2D_SpriteSheetFree(bgSprites);	
		C2D_SpriteSheetFree(mcLogo);
		C2D_SpriteSheetFree(dirtBg);
		C2D_SpriteSheetFree(buttonSprSh);

		C2D_FontFree(mcFont);

		for(auto el : btns){
			el.unload();			
		}
	}

	~TitleScene()
	{
		unload();
	}
};