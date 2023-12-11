#pragma once
#include <iostream>
#include "engine.h"
#include "button.hpp"

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

	Button singlePlrBtn;


public:
 	
	TitleScene()
	{

	}

	void update()
	{
		if(currFrame == 1)
			currFrame = 0;
		else if(currFrame == 0)
			currFrame = 1;

		C2D_SpriteFromSheet(&bgSpr, bgSprites, currFrame);
		C2D_SpriteScale(&bgSpr, .666, .5325); 
	}

	void drawTop()
	{
		C2D_DrawSprite(&bgSpr);
		C2D_DrawSprite(&mcLogoSpr);
		
	}

	void drawBottom()
	{
		C2D_DrawSprite(&dirtSpr);
		singlePlrBtn.render();
	}

	void start()
	{
		C2D_SpriteFromSheet(&mcLogoSpr, mcLogo, 0);
		C2D_SpriteScale(&mcLogoSpr, 1, 1); 
		C2D_SpriteSetCenter(&mcLogoSpr, 0.5f, 0.5f);
		C2D_SpriteSetPos(&mcLogoSpr,TOP_SCREEN_WIDTH/2, TOP_SCREEN_HEIGHT/2);

		C2D_SpriteFromSheet(&dirtSpr, dirtBg, 0);
		C2D_SpriteScale(&dirtSpr, 1, 1); 
	
		singlePlrBtn = 	Button(&buttonSprSh, "Singleplayer", &mcFont, C2D_Color32f(1.0f, 1.0f, 1.0f, 1.0f), BOTTOM_SCREEN_WIDTH /4, 8, 678, 78);

	}

	void load()
	{
		bgSprites = C2D_SpriteSheetLoad("romfs:/gfx/bg.t3x");
		mcLogo = C2D_SpriteSheetLoad("romfs:/gfx/logo.t3x");
		dirtBg = C2D_SpriteSheetLoad("romfs:/gfx/dirt-bg.t3x");
		buttonSprSh = C2D_SpriteSheetLoad("romfs:/gfx/button.t3x");

		mcFont = C2D_FontLoad("romfs:/mcfont.bcfnt");
	}

	void unload()
	{
		C2D_SpriteSheetFree(bgSprites);	
		C2D_SpriteSheetFree(mcLogo);
		C2D_SpriteSheetFree(dirtBg);
		C2D_SpriteSheetFree(buttonSprSh);

		C2D_FontFree(mcFont);

		singlePlrBtn.unload();
	}

	~TitleScene()
	{
		unload();
	}
};