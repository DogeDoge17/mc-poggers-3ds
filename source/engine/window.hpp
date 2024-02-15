#pragma once
#include <string>
#include "input.hpp"
#include "debug.hpp"
#include <math.h> 

namespace window{

	std::vector<std::string> queue;

	bool enabled = false;

	std::string activeText;


	C2D_TextBuf mainBuf;
	C2D_Text mainText;

	C2D_TextBuf titleBuf;
	C2D_Text titleText;

	C2D_Font font;

	int queueIndex = 0;

	void parse(){
		if(queueIndex >= (int)queue.size())
		{
			queueIndex = 0;
			activeText = "";
			queue = {};
			C2D_TextBufClear(mainBuf);	
			enabled = false;
		}
		activeText = queue[queueIndex];
		C2D_TextBufClear(mainBuf);	
	    C2D_TextFontParse(&mainText, font, mainBuf, activeText.c_str());
		C2D_TextOptimize(&mainText);
		/*if(queue.size() > 0)
		{
			activeText = queue[0];
			C2D_TextBufClear(mainBuf);
			C2D_TextFontParse(&mainText, font, mainBuf, activeText.c_str());
			C2D_TextOptimize(&mainText);
			queue.erase(queue.begin());
			Debugger::WriteLine("Queue size: " + std::to_string(queue.size()));
		}*/
	}

	void init(){
		mainBuf = C2D_TextBufNew(4090);
		titleBuf = C2D_TextBufNew(4090);
		font = C2D_FontLoadSystem(CFG_REGION_USA);

		C2D_TextFontParse(&titleText, font, titleBuf, "This homebrew app says");
		C2D_TextOptimize(&titleText);
	}


	void confirm(std::string text){
		enabled = true;
		queue.push_back(text);

		parse();

		/*queue.push_back(text);

		Debugger::WriteLine(text + " added to queue");

		enabled = true;
		if(queue.size() == 1){

			parse();
		}*/
	}




	void advance(){
		queueIndex++;
		parse();
		
		/*if(queue.size() > 0)
		{
			Debugger::WriteLine("queue big. parsing");
			parse();
		}else{
			Debugger::WriteLine("queue empty. disabling");
			enabled = false;
		}*/
	}

	void update()
	{
		if(Input::GetKeyDown(KeyCode::B) || Input::GetKeyDown(KeyCode::A))
		{
			Debugger::WriteLine("Close event triggered");
			advance();
		}
	}

	constexpr std::tuple<int,int> tlCorn = {static_cast<int>(floor(TOP_SCREEN_WIDTH /4)), 0};

	void renderTop()
	{
		if(!enabled)
			return;
					
		C2D_DrawRectSolid(0, 0, 0, TOP_SCREEN_WIDTH, TOP_SCREEN_HEIGHT, C2D_Color32f(0, 0, 0, .5f));
		C2D_DrawRectSolid(std::get<0>(tlCorn), std::get<1>(tlCorn), 0, static_cast<int>(floor(TOP_SCREEN_WIDTH /2)), static_cast<int>(floor(TOP_SCREEN_HEIGHT/2)), C2D_Color32f(0.2588f, 0.2549f, 0.302f, 1));
		C2D_DrawText(&titleText, C2D_WithColor, std::get<0>(tlCorn) +5, std::get<1>(tlCorn)+5, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f);
		C2D_DrawText(&mainText, C2D_WithColor, std::get<0>(tlCorn) + 5, std::get<1>(tlCorn) + 40, 0.5f, 0.5f, 1.0f, 1.0f, 1.0f);		
	}

	void renderBottom()
	{
		if(!enabled)
			return;
	
		C2D_DrawRectSolid(0, 0, 0.5f, TOP_SCREEN_WIDTH, BOTTOM_SCREEN_HEIGHT, C2D_Color32f(0, 0, 0, .5f));
	}

	void sceneExit(){
		C2D_TextBufDelete(mainBuf);
		C2D_FontFree(font);
	}

};