#include <citro2d.h>

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOP_SCREEN_WIDTH  400
#define TOP_SCREEN_HEIGHT 240 


#define BOTTOM_SCREEN_WIDTH  320 
#define BOTTOM_SCREEN_HEIGHT 240 

#include "engine/sceneManage.hpp"
#include "engine/time.hpp"
#include "engine/input.hpp"
#include "game/titleScreen.hpp"

#include "engine/debug.hpp"
#include "engine/window.hpp"


static C2D_SpriteSheet spriteSheet;

//int fart;
void Update()
{
	

	if((Input::GetKeyDown(KeyCode::Start) && Input::GetKeyDown(KeyCode::Select)) || Input::GetKeyDown(KeyCode::ZR))
	{
		Debugger::Toggle();
	}
}


//---------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
//---------------------------------------------------------------------------------
	// Init libs
	romfsInit();
	cfguInit(); 
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	Debugger::init();
	window::init();
	//consoleInit(GFX_BOTTOM, NULL);

	// Create screens
	C3D_RenderTarget* top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
	C3D_RenderTarget* bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);

	SceneManagement::loadScene<TitleScene>();
	SceneManagement::loadScene<TitleScene>();

  spriteSheet = C2D_SpriteSheetLoad("romfs:/gfx/sprites.t3x");
  if (!spriteSheet) svcBreak(USERBREAK_PANIC);

	// Main loop
	while (aptMainLoop())
	{
		hidScanInput();

		Time::SetTime();
		
		Update();
    if(window::enabled)
      window::update();
    else
      SceneManagement::activeScene->update();

    SceneManagement::activeScene->prerender();

    C2D_Prepare();
    C3D_DepthTest(false, GPU_ALWAYS, GPU_WRITE_COLOR);
    /* top screen */{
      C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
      C2D_TargetClear(top, C2D_Color32f(1.0f, 1.0f, 1.0f, 1.0f));
      C2D_SceneBegin(top);

      SceneManagement::activeScene->drawTop();

      if(window::enabled) window::renderTop();
      C3D_FrameEnd(0);
    }

    /* bottom screen */ {
      C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
      C2D_TargetClear(bottom, C2D_Color32f(1.0f, 1.0f, 1.0f, 1.0f));
      C2D_SceneBegin(bottom);

      if(Debugger::enabled)
        Debugger::render();
      else{
        SceneManagement::activeScene->drawBottom();
        if(window::enabled) window::renderBottom();
      }

      C3D_FrameEnd(0);
    }

		Input::Update();
	}

	Debugger::exit();
	window::sceneExit();
	C2D_Fini();
	C3D_Fini();
	gfxExit();
	cfguExit();
	romfsExit();
	return 0;
}
