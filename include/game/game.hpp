#pragma once
#include <iostream>
#include <bits/stdc++.h> 
#include <iomanip>
#include <array>
#include <unordered_map>
#include <citro2d.h>
#include <3ds.h>
#include "engine/sceneManage.hpp"
#include "button.hpp"
#include "label.hpp"

class TitleScene;

#define TOP_SCREEN_WIDTH  400
#define TOP_SCREEN_HEIGHT 240 
#define BOTTOM_SCREEN_WIDTH  320 
#define BOTTOM_SCREEN_HEIGHT 240

class GameScene final : public Scene
{
private:
	// UI VARS
	std::unordered_map<std::string, C2D_SpriteSheet> sshs;

	C2D_Font mcFont;
	C2D_SpriteSheet heartSSheet;
	std::array<C2D_Sprite,10> hearts;
	std::array<C2D_DrawParams,10> heartsParams;

 	C2D_SpriteSheet buttonSprSh;

	std::array<Button,2> faceBtns;
	int selectedFaceBtn;

	Label enemyHealthLbl;
	Label heartDebug;

	C2D_Sprite steveSprite;
	C2D_DrawParams steveParams;

	C2D_Sprite zombieSprite;
	C2D_DrawParams zombieParams;
	
	// GAME VARS
	int enemyHealth;
	int playerHealth;
	bool pp;

	bool attackStart;
	int pressOne;
	int pressOneZ;

	std::array<float,2> enemyAttack;
	int AttackDamage;
	bool revived;  

	int activeFood;
	std::array<int,2> foodLeft;

	void updateHealthSystem();
	void deadZombie();
	void heal();
	void attack();

public:
	GameScene();
	void load() override;
	void start() override;
	void update() override;
	void drawTop() override;
	void drawBottom() override;
	void unload() override;
	~GameScene() override;
};
