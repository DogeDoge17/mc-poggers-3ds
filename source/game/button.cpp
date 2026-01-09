#include "game/button.hpp"
#include "engine/input.hpp"

Button::Button(){}

Button::Button(C2D_SpriteSheet* buttonBg, std::string btnText, C2D_Font* buttonFont, u32 textColour, int xPos, int yPos, float btnWidth, float btnHeight)
{
	texture = buttonBg;
	text = btnText;
	x = xPos;
	y = yPos;
	xScale = btnWidth;
	yScale = btnHeight;

	font = buttonFont;

	colour = textColour;

	g_staticBuf  = C2D_TextBufNew(4096);
	C2D_TextFontParse(&g_staticText, *font, g_staticBuf, text.c_str());
	C2D_TextOptimize(&g_staticText);

	C2D_SpriteFromSheet(&currSprite, *texture, 0);
	C2D_SpriteScale(&currSprite, xScale, yScale);
	C2D_SpriteSetCenter(&currSprite, centreX, centreY);

	C2D_SpriteSetPos(&currSprite, x, y);
}

void Button::updateText(std::string newText){
	text = newText;

	C2D_TextBufClear(g_staticBuf);
	
	C2D_TextFontParse(&g_staticText, *font, g_staticBuf, text.c_str());
	C2D_TextOptimize(&g_staticText);
}

void Button::changedSelected(int sel)
{
	selected = sel;		
	
	if(selected == 1){
		C2D_SpriteFromSheet(&currSprite, *texture, 1);
	}else if (selected == 0){
		C2D_SpriteFromSheet(&currSprite, *texture, 0);
	}

	C2D_SpriteScale(&currSprite, xScale, yScale);
	C2D_SpriteSetCenter(&currSprite, centreX, centreY);
	C2D_SpriteSetPos(&currSprite, x, y);
}

bool Button::checkPressed()
{
	TouchInfo touch = Input::GetTouchDown();
	
	if(touch.validTouch)
	{
		if(touch.pos.px >= x - (currSprite.params.pos.w / 2) && touch.pos.px <= x + (currSprite.params.pos.w / 2) && touch.pos.py >= y - (currSprite.params.pos.h / 2) && touch.pos.py <= y + (currSprite.params.pos.h / 2))
		{
			return true;
		}
	}
	return false;
}

void Button::render(){
	C2D_DrawSprite(&currSprite);
	float outWidth = 0;
	float outHeight = 0;
	C2D_TextGetDimensions(&g_staticText, textScaleX, textScaleY, &outWidth, &outHeight);
	C2D_DrawText(&g_staticText, C2D_AlignCenter | C2D_WithColor, x + textScaleX, y - (outHeight/2), 0, textScaleX, textScaleY, colour);
}

void Button::unload()
{
	C2D_TextBufDelete(g_staticBuf);
}
