#pragma once
#include <iostream>
#include <array>
#include <citro2d.h>
#include <3ds.h>
#include "engine/sceneManage.hpp"
#include "button.hpp"
#include "label.hpp"

class MultiplayerScene;
class GameScene;

#define TOP_SCREEN_WIDTH  400
#define TOP_SCREEN_HEIGHT 240 
#define BOTTOM_SCREEN_WIDTH  320 
#define BOTTOM_SCREEN_HEIGHT 240

class TitleScene : public Scene
{
private:
 	C2D_SpriteSheet mcLogo;
 	C2D_SpriteSheet dirtBg;
 	C2D_SpriteSheet buttonSprSh;

	C2D_Sprite mcLogoSpr;
	C2D_Sprite dirtSpr;

	C2D_Font mcFont;

	std::array<Button, 3> btns;

	int selectedButton;

	Label creds;

public:
	TitleScene();
	void load() override;
	void start() override;
	void update() override;
	void drawTop() override;
	void drawBottom() override;
	void unload() override;
	~TitleScene() override;
};
