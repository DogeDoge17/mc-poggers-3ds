#include "game/game.hpp"
#include "game/titleScreen.hpp"
#include "game/button.hpp"
#include "game/label.hpp"
#include "game/engine.h"

GameScene::GameScene()
{
	selectedFaceBtn = 0;
	enemyHealth = 50;
	playerHealth = 20;
	pp = false;
	attackStart = false;
	pressOne = 1;
	pressOneZ = 1;
	enemyAttack = {3.5,4};
	AttackDamage = 3;
	revived = false;
	activeFood = 0;
	foodLeft = {4,2};
}

void GameScene::updateHealthSystem() {
	if(playerHealth <= 0){
		playerHealth = 0;
	}

	const float currentHealth = playerHealth /2;

	for (int i = 0; i < 10; i++)
	{
		if (i < currentHealth)
		{
			C2D_SpriteFromSheet(&hearts[i], sshs["hearts"], 2);			
			hearts[i].params = heartsParams[i];
		} else if (i == (int)ceil(currentHealth) && fmod(currentHealth, 1) != 0) 
		{
			C2D_SpriteFromSheet(&hearts[i], sshs["hearts"], 1);
			hearts[i].params = heartsParams[i];
		} else 
		{
			C2D_SpriteFromSheet(&hearts[i], sshs["hearts"], 0);
			hearts[i].params = heartsParams[i];
		}
	}

	Debugger::WriteLine(std::to_string(playerHealth));
	
	if (playerHealth > 20) {
		playerHealth = 20;
	}
}

void GameScene::deadZombie()
{
	// Implementation commented out in original
}

void GameScene::heal()
{
	Debugger::WriteLine(std::to_string(playerHealth));

	if(playerHealth > 0 && playerHealth < 20)
	{
		if(activeFood == 0) 
		{   
			if(foodLeft[activeFood] > 0)
			{
				playerHealth += 8;  
				foodLeft[0] -= 1;
				updateHealthSystem();
			}else
			{
				window::confirm("No more steak");
			}     
		}
		
		if(activeFood == 1)
		{
			if(foodLeft[activeFood] > 0)
			{  
				playerHealth += 8;
				foodLeft[1] -= 1;
				updateHealthSystem();
			}else
			{
				window::confirm("No more porkchops");
			}     
		}

	}else if(playerHealth == 20)
	{
		window::confirm("You can't eat anymore");
	}else if(playerHealth <= 0)
	{
		window::confirm("Dead people can't eat");
	}
}

void GameScene::attack()
{
	if(enemyHealth <= 0 && !revived){
		deadZombie();	
		enemyHealth = 0;
	}

	if(enemyHealth > 0 && playerHealth > 0 && !revived)
	{
		if(enemyHealth > AttackDamage)
			enemyHealth -= AttackDamage;
		else {
			enemyHealth = 0;
			deadZombie();
		}
	}
	enemyHealthLbl.updateText("Zombie Health: " + std::to_string(enemyHealth));
	
	if(enemyHealth > 0)
		playerHealth -= enemyAttack[0];
	
	updateHealthSystem();	

	if(revived)
	{
		revived = false;    
	}
}

void GameScene::load()
{
	mcFont = C2D_FontLoad("romfs:/mcfont.bcfnt");
	sshs["hearts"] = C2D_SpriteSheetLoad("romfs:/gfx/hearts.t3x");
	sshs["button"] = C2D_SpriteSheetLoad("romfs:/gfx/button.t3x");

	sshs["steve"] = C2D_SpriteSheetLoad("romfs:/gfx/steve.t3x");
	sshs["zombie"] = C2D_SpriteSheetLoad("romfs:/gfx/zombie.t3x");
}

void GameScene::start()
{
	constexpr float heartScale = 3;
	constexpr float totalWidth = hearts.size() * heartScale * 10;
	constexpr float startX = (BOTTOM_SCREEN_WIDTH - totalWidth) / 2.0f;

	for (int i = 0; i < static_cast<int>(hearts.size()); i++) 
	{
		const float heartY = 4;
		C2D_SpriteFromSheet(&hearts[i], sshs["hearts"], 2);

		float xOffset = startX + i * heartScale * 10;
		C2D_SpriteSetPos(&hearts[i], xOffset, heartY);

		C2D_SpriteSetScale(&hearts[i], heartScale, heartScale);
		heartsParams[i] = hearts[i].params;
	}

	faceBtns[0] = Button(&sshs["button"], "Attack", &mcFont, C2D_Color32f(1.0f, 1.0f, 1.0f, 1.0f), BOTTOM_SCREEN_WIDTH /4, BOTTOM_SCREEN_HEIGHT/2, .17, .5f);		
	faceBtns[1] = Button(&sshs["button"], "Heal", &mcFont, C2D_Color32f(1.0f, 1.0f, 1.0f, 1.0f), BOTTOM_SCREEN_WIDTH /4 + (BOTTOM_SCREEN_WIDTH /2) ,  BOTTOM_SCREEN_HEIGHT/2, .18, .5f);

	faceBtns[0].changedSelected(1);

	enemyHealthLbl = Label("Zombie Health: " + std::to_string(enemyHealth), &mcFont, C2D_Color32f(0.0f, 0.0f, 0.0f, 1.0f), BOTTOM_SCREEN_WIDTH /2, 66, .6f, .6f);
	enemyHealthLbl.makeCentreY();
	enemyHealthLbl.flags = C2D_AlignCenter;
	enemyHealthLbl.wordWrap = BOTTOM_SCREEN_WIDTH;

	C2D_SpriteFromSheet(&steveSprite, sshs["steve"], 0);
	C2D_SpriteScale(&steveSprite, .5f, .5f); 
	C2D_SpriteSetCenter(&steveSprite, 0, 1);
	C2D_SpriteSetPos(&steveSprite, 0, TOP_SCREEN_HEIGHT);

	C2D_SpriteFromSheet(&zombieSprite, sshs["zombie"], 0);
	C2D_SpriteScale(&zombieSprite, .75f, .75f); 
	C2D_SpriteSetCenter(&zombieSprite, 0, 1);
	C2D_SpriteSetPos(&zombieSprite, steveSprite.params.pos.w, TOP_SCREEN_HEIGHT);
}

void GameScene::update()
{
	if(Input::GetKeyDown(KeyCode::Start)){
		SceneManagement::loadScene<TitleScene>();
		return;
	}

	bool change = false;
	if(Input::GetKeyDown(KeyCode::Right)){
		selectedFaceBtn++;
		if(selectedFaceBtn > static_cast<int>(faceBtns.size())-1)
			selectedFaceBtn = 0;
		change = true;
	}
	if(Input::GetKeyDown(KeyCode::Left))
	{
		selectedFaceBtn--;
		if(selectedFaceBtn < 0)
			selectedFaceBtn = static_cast<int>(faceBtns.size())-1;
		change = true;
	}

	if(Input::GetKeyDown(KeyCode::L)){
		if(activeFood > 0)
		{
			activeFood -= 1;
		}
	}
	
	if(Input::GetKeyDown(KeyCode::R))
	{
		if(activeFood < static_cast<int>(foodLeft.size()) - 1)
		{
			activeFood += 1;
		}
	}

	if(change)
	{
		for(auto & faceBtn : faceBtns)
		{
			faceBtn.changedSelected(0);
		}

		faceBtns[selectedFaceBtn].changedSelected(1);
	}

	if (Input::GetKeyDown(KeyCode::ZL))
	{
		window::confirm("hi");
		window::confirm("hi2");
		window::confirm("hi3");
		window::confirm("hi4");
	}

	if(Input::GetKeyDown(KeyCode::A))
	{
		switch(selectedFaceBtn)
		{
			case 0:
				attack();
				break;
			case 1:
				heal();
				break;
			default: ;
		}
	}

	for(int i = 0; i < static_cast<int>(faceBtns.size()); i++)
	{
		if(faceBtns[i].checkPressed())
		{
			for(auto & faceBtn : faceBtns)
			{
				faceBtn.changedSelected(0);
			}	

			faceBtns[i].changedSelected(1);
			selectedFaceBtn = i;
			switch(i)
			{
				case 0:
					attack();
					break;
				case 1:
					heal();
					break;
				default: ;
			}
		}
	}
}

void GameScene::drawTop()
{
	C2D_DrawSprite(&steveSprite);
	C2D_DrawSprite(&zombieSprite);
}

void GameScene::drawBottom()
{
	for(auto & heart : hearts)
		C2D_DrawSprite(&heart);

	for(auto & faceBtn : faceBtns)
		faceBtn.render();
	enemyHealthLbl.render();
}	

void GameScene::unload()
{
	for (const auto& pair : sshs) {
		C2D_SpriteSheetFree(pair.second);
	}
}

GameScene::~GameScene()
{
	GameScene::unload();
}
