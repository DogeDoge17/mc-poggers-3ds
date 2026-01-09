#pragma once
#include <string.h>
#include <citro2d.h>
#include <3ds.h>
#include <string>

class Label
{
private:
	C2D_TextBuf g_staticBuf;
	C2D_Text g_staticText;

public:
	int x, y, z = 0;
	float xScale = 1;
	float yScale = 1;
	std::string text;

	C2D_Font* font;

	float textScaleX = 0.5f;
	float textScaleY = 0.5f;

	u32 flags;
	u32 colour;
	int wordWrap;

	Label();
	Label(std::string lblText, C2D_Font* lblFont);
	Label(std::string lblText, C2D_Font* lblFont, u32 textColour, int xPos, int yPos, float fontSize);
	Label(std::string lblText, C2D_Font* lblFont, u32 textColour, int xPos, int yPos, float xScale, float yScale);

	void updateText(std::string newText);
	void makeCentreY();
	void render();
	void unload();
};
