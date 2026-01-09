#pragma once

#include <string>
#include <citro2d.h>
#include <3ds.h>

#define TOP_SCREEN_WIDTH  400
#define TOP_SCREEN_HEIGHT 240 
#define BOTTOM_SCREEN_WIDTH  320 
#define BOTTOM_SCREEN_HEIGHT 240

namespace Debugger
{
	extern std::string wholeConsole;
	extern bool enabled;
	extern C2D_TextBuf g_staticBuf;
	extern C2D_Text g_staticText;
	extern C2D_Font font;
	extern size_t bufferSize;
	extern size_t maxConsoleSize;

	void Toggle();
	void init();
	void Write(std::string additionalText);
	void Clear();
	void WriteLine(std::string additionalText);
	void render();
	void exit();
};
