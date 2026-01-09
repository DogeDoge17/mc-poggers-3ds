#pragma once
#include <string.h>
#include <citro2d.h>
#include <3ds.h>
#include <string>

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

	float textScaleX = 0.5f;
	float textScaleY= 0.5f;

	Button();
	Button(C2D_SpriteSheet* buttonBg, std::string btnText, C2D_Font* buttonFont, u32 textColour, int xPos, int yPos, float btnWidth, float btnHeight);
	
	void updateText(std::string newText);
	void changedSelected(int sel);
	bool checkPressed();
	void render();
	void unload();
};
