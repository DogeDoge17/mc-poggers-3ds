#pragma once

#include <string.h>
#include <citro2d.h>
#include <3ds.h>

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

	Label(){}

	Label(std::string lblText, C2D_Font* lblFont)
	{
		text = lblText;
		x = 0;
		y = 0;

		font = lblFont;

		g_staticBuf  = C2D_TextBufNew(4096);
		C2D_TextFontParse(&g_staticText, *font, g_staticBuf, text.c_str());
		C2D_TextOptimize(&g_staticText);

	}
	Label(std::string lblText, C2D_Font* lblFont, u32 textColour, int xPos, int yPos, float fontSize)
	{
		Label(lblText, lblFont, textColour,  xPos,  yPos, fontSize, fontSize);
	}

	Label(std::string lblText, C2D_Font* lblFont, u32 textColour, int xPos, int yPos, float xScale, float yScale)
	{
		text = lblText;
		x = xPos;
		y = yPos;

		textScaleX = xScale;
		textScaleY = yScale;

		font = lblFont;

		g_staticBuf  = C2D_TextBufNew(4096);
		C2D_TextFontParse(&g_staticText, *font, g_staticBuf, text.c_str());
		C2D_TextOptimize(&g_staticText);
		colour = textColour;
	}

	void updateText(std::string newText){
		text = newText;

		C2D_TextBufClear(g_staticBuf);
		
		C2D_TextFontParse(&g_staticText, *font, g_staticBuf, text.c_str());
		C2D_TextOptimize(&g_staticText);
	}

	void makeCentreY()
	{
		float outX;
		float outY;
		C2D_TextGetDimensions(&g_staticText, textScaleX, textScaleY, &outX, &outY);
		y = y - (outY/2);
	}

	void render()
	{
		if(flags == 0)
			C2D_DrawText(&g_staticText, C2D_WithColor, x, y, z, textScaleX, textScaleY, colour);	
		else
			C2D_DrawText(&g_staticText, C2D_WithColor | flags, x, y, z, textScaleX, textScaleY, colour, wordWrap);	
	}

	void unload()
	{
		C2D_TextBufDelete(g_staticBuf);

	}	
};