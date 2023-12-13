#pragma once

#include <string.h>
#include <citro2d.h>
#include <3ds.h>

class Button
{
private:
	C2D_TextBuf g_staticBuf;
	C2D_Text g_staticText;

public:
	C2D_SpriteSheet* texture;
	C2D_Sprite currSprite;

	int x, y;
	float xScale = 1;
	float yScale = 1;
	std::string text;
	u32 colour;

	C2D_Font* font;

	int selected;

    float centreX = 0.5f;
 	float centreY = 0.5f;

	Button(){}


	Button(C2D_SpriteSheet* buttonBg, std::string btnText, C2D_Font* buttonFont, u32 textColour, int xPos, int yPos, float btnWidth, float btnHeight)
	{
		texture = buttonBg;
		text = btnText;
		x = xPos;
		y = yPos;
		xScale = btnWidth;
		yScale = btnHeight;

		font = buttonFont;

		g_staticBuf  = C2D_TextBufNew(4096);
		C2D_TextFontParse(&g_staticText, *font, g_staticBuf, btnText.c_str());
		C2D_TextOptimize(&g_staticText);

		C2D_SpriteFromSheet(&currSprite, *texture, 0);
		C2D_SpriteScale(&currSprite, xScale, yScale);
		C2D_SpriteSetCenter(&currSprite, centreX, centreY);

		C2D_SpriteSetPos(&currSprite, x, y);
	}

	void updateText(std::string newText){
		text = newText;

		C2D_TextFontParse(&g_staticText, *font, g_staticBuf, newText.c_str());
		C2D_TextOptimize(&g_staticText);
	}

	void render(){
		C2D_DrawSprite(&currSprite);
		C2D_DrawText(&g_staticText, C2D_WithColor, x, y, 0, 0.5f, 0.5f, C2D_Color32f(1.0f, 1.0f, 1.0f, 1.0f));
	}

	void unload()
	{
		C2D_TextBufDelete(g_staticBuf);
	}	

};