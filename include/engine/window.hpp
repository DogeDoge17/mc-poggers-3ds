#pragma once
#include <string>
#include <vector>
#include <tuple>
#include <citro2d.h>
#include <3ds.h>

#define TOP_SCREEN_WIDTH  400
#define TOP_SCREEN_HEIGHT 240 
#define BOTTOM_SCREEN_WIDTH  320 
#define BOTTOM_SCREEN_HEIGHT 240

namespace window{
	extern std::vector<std::string> queue;
	extern bool enabled;
	extern std::string activeText;
	extern C2D_TextBuf mainBuf;
	extern C2D_Text mainText;
	extern C2D_TextBuf titleBuf;
	extern C2D_Text titleText;
	extern C2D_Font font;
	extern int queueIndex;

	void parse();
	void init();
	void confirm(std::string text);
	void advance();
	void update();
	void renderTop();
	void renderBottom();
	void sceneExit();
};
