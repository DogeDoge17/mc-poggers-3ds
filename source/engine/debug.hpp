#pragma once

#include <string>


namespace Debugger
{
	std::string wholeConsole;

	bool enabled = false;

	C2D_TextBuf g_staticBuf;
	C2D_Text g_staticText;
	C2D_Font font;


	size_t bufferSize = 4090;
	size_t maxConsoleSize = 1000;


	void Toggle()
	{
		enabled = !enabled;
	}

	void init(){
		g_staticBuf = C2D_TextBufNew(bufferSize);
		font = C2D_FontLoadSystem(CFG_REGION_USA);

		C2D_TextFontParse(&g_staticText, font, g_staticBuf, "> (nothing logged)");
		C2D_TextOptimize(&g_staticText);

	}

	void Write(std::string additionalText){
		wholeConsole = additionalText + wholeConsole;


          if (wholeConsole.size() > maxConsoleSize) {
            wholeConsole = wholeConsole.substr(0, maxConsoleSize);
        }

		C2D_TextBufClear(g_staticBuf);
		C2D_TextFontParse(&g_staticText, font, g_staticBuf, wholeConsole.c_str());
		C2D_TextOptimize(&g_staticText);

	}

	void Clear(){
		wholeConsole = "";
		C2D_TextBufClear(g_staticBuf);
		g_staticBuf = C2D_TextBufNew(bufferSize);
	}

	void WriteLine(std::string additionalText)
	{
		Write("> " + additionalText + "\n");
	}

	void render()
	{
		if(!enabled)
			return;

		C2D_DrawRectSolid(0, 0, 0, BOTTOM_SCREEN_WIDTH, BOTTOM_SCREEN_HEIGHT, C2D_Color32f(0, 0, 0, 1));

		C2D_DrawText(&g_staticText, C2D_WithColor , 8.0f, 8.0f, 0.5f, 0.5f, 0.5f, C2D_Color32f(1, 1, 1, 1));
	}

	void exit(){
		C2D_FontFree(font);
		C2D_TextBufDelete(g_staticBuf);
	}
};