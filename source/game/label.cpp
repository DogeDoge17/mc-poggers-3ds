#include "game/label.hpp"

Label::Label(){}

Label::Label(std::string lblText, C2D_Font* lblFont)
{
	text = lblText;
	x = 0;
	y = 0;

	font = lblFont;

	g_staticBuf  = C2D_TextBufNew(4096);
	C2D_TextFontParse(&g_staticText, *font, g_staticBuf, text.c_str());
	C2D_TextOptimize(&g_staticText);
}

Label::Label(std::string lblText, C2D_Font* lblFont, u32 textColour, int xPos, int yPos, float fontSize)
{
	Label(lblText, lblFont, textColour,  xPos,  yPos, fontSize, fontSize);
}

Label::Label(std::string lblText, C2D_Font* lblFont, u32 textColour, int xPos, int yPos, float xScale, float yScale)
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

void Label::updateText(std::string newText){
	text = newText;

	C2D_TextBufClear(g_staticBuf);
	
	C2D_TextFontParse(&g_staticText, *font, g_staticBuf, text.c_str());
	C2D_TextOptimize(&g_staticText);
}

void Label::makeCentreY()
{
	float outX;
	float outY;
	C2D_TextGetDimensions(&g_staticText, textScaleX, textScaleY, &outX, &outY);
	y = y - (outY/2);
}

void Label::render()
{
	if(flags == 0)
		C2D_DrawText(&g_staticText, C2D_WithColor, x, y, z, textScaleX, textScaleY, colour);	
	else
		C2D_DrawText(&g_staticText, C2D_WithColor | flags, x, y, z, textScaleX, textScaleY, colour, wordWrap);	
}

void Label::unload()
{
	C2D_TextBufDelete(g_staticBuf);
}
