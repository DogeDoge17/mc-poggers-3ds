#pragma once
#include <iostream>
#include <bits/stdc++.h> 
#include <iomanip>
#include <array>
#include <unordered_map>
#include <citro2d.h>
#include <3ds.h>
#include "engine/sceneManage.hpp"

class TitleScene;
class Button;
class Label;

class MultiplayerScene : public Scene
{
private:
 	C2D_SpriteSheet dirtBg;
	C2D_Sprite dirtSpr;

 	C2D_SpriteSheet trollSheet;
 	C2D_SpriteSheet trollSheet2;
	std::array<C2D_Sprite,4> trollSprites;

	float scrollPos;

public:
	MultiplayerScene();
	void load() override;
	void start() override;
	void update() override;
	void drawTop() override;
	void drawBottom() override;
	void unload() override;
	~MultiplayerScene() override;
};
