#pragma once
#include <iostream>
#include "engine.h"
#include "titleScreen.hpp"
#include <bits/stdc++.h> 
#include <iomanip>
#include "Label.hpp"

class TitleScene;

class GameScene : public Scene
{
private:

///----------------UI VARS----------------///

	//all the sprite sheets in a dictionary so i dont forget to free them
	std::unordered_map<std::string, C2D_SpriteSheet> sshs;

	C2D_Font mcFont;
	C2D_SpriteSheet heartSSheet;
	std::array<C2D_Sprite,10> hearts;
	std::array<C2D_DrawParams,10> heartsParams;

 	C2D_SpriteSheet buttonSprSh;

	std::array<Button,2> faceBtns;
	int selectedFaceBtn = 0;

	Label enemyHealthLbl;
	Label heartDebug;

	C2D_Sprite steveSprite;
	C2D_DrawParams steveParams;

	C2D_Sprite zombieSprite;
	C2D_DrawParams zombieParams;
	
///----------------END--------------------///

///----------------GAME VARS--------------///
	int enemyHealth = 50;
	int playerHealth = 20;
	bool pp = false;

	bool attackStart = false;
	int pressOne = 1;
	int pressOneZ = 1;

	std::array<float,2> enemyAttack = {3.5,4};
	int AttackDamage = 3;
	bool revived = false;  
    
	//var actionConsole;

	int activeFood = 0;
	std::array<int,2> foodLeft = {4,2}; //steak, porkchops  

///----------------END--------------------///


public:
 	
	GameScene()
	{

	}

///-------------GAME FUNCTIONS------------///

void updateHealthSystem() {


	if(playerHealth <= 0){
		playerHealth = 0;
	}

	float currentHealth = playerHealth /2;

	for (int i = 0; i < 10; i++)
	{
		//C2D_Sprite* heart = &hearts[i];

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



    /*for (int i = 10; i >= 0; i--) {
        if (playerHealth <= (i * 2 - 1) && playerHealth > (i * 2 - 2)) {
			C2D_SpriteFromSheet(&hearts[i], sshs["hearts"], 1);
			hearts[i].params = heartsParams[i];
			
			//Debugger::WriteLine("Heart " + std::to_string(i) + " drew as a half heart");
        } else if (playerHealth <= (i * 2 - 2)) {
			C2D_SpriteFromSheet(&hearts[i], sshs["hearts"], 0);
			hearts[i].params = heartsParams[i];
			
			//Debugger::WriteLine("Heart " + std::to_string(i) + " drew as an empty heart");
        } else {
			C2D_SpriteFromSheet(&hearts[i], sshs["hearts"], 2);			
			hearts[i].params = heartsParams[i];
			
			//Debugger::WriteLine("Heart " + std::to_string(i) + " drew as a full heart");
        }
    }*/ 

     
	Debugger::WriteLine(std::to_string(playerHealth));
    // Ensure playerHealth is capped at 20
    if (playerHealth > 20) {
        playerHealth = 20;
    }
}


void deadZombie()
{
	/*//window.confirm("You win.");
    
	   document.getElementById("zombieImage").src="assets/images/deadZombie.jpeg"
	   document.getElementById("zombieImage").style.width = "200px"
    
    enemyHealth = 0;   
    document.getElementById("zombieHealthLbl").innerHTML = "Zombie Health: 0";
    
    
    
    if(pressOneZ == 1)
    {
        pressOneZ += 1;    
        window.confirm("You win.");
        revived = false
    }
    else if(pressOneZ == 2)
    {
        pressOneZ += 1;    
        window.confirm(".");
    }
    else if(pressOneZ == 3)
    {
        pressOneZ += 1;    
        window.confirm("..");
    }
    else if(pressOneZ == 4)
    {
        pressOneZ += 1;    
        window.confirm("...");
    }
    else if(pressOneZ == 5)
    {
        pressOneZ += 1;    
        window.confirm("Dude");
    }else if(pressOneZ == 6)
    {
        window.confirm("Stop it")
        pressOneZ += 1;
    }else if(pressOneZ == 7)
    {
        window.confirm("You've made your point")
        pressOneZ += 1;
    }else if(pressOneZ == 8)
    {
        window.confirm("Really")
        pressOneZ += 1;
    }else if(pressOneZ == 9)
    {
        window.confirm("Stop")
        pressOneZ += 1;
    }else if(pressOneZ == 10)
    {
        window.confirm("I'm warning you")
        pressOneZ += 1;
    }else if(pressOneZ == 11)
    {
        window.confirm("Last Chance")
        pressOneZ += 1;
    }else if(pressOneZ == 12)
    {
        window.confirm("idot 🙄.")
        pressOneZ = 0;
        enemyHealth = 20;
        document.getElementById("zombieHealthLbl").innerHTML = "Zombie Health: 20";
        document.getElementById("zombieImage").src="assets/images/zombie.png";
        //document.getElementById("zombieImage").style.width = "500px"
        revived = true;
        return;
        
    }*/
}


void heal()
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

void attack()
{
	if(enemyHealth <= 0 && !revived){
		deadZombie();	
        enemyHealth = 0;
        
	}

	if(enemyHealth > 0 && playerHealth > 0 && !revived)
    {
       if(enemyHealth > AttackDamage)
	       enemyHealth -= AttackDamage;
        else{
            
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

///----------------END--------------------///


	void load()
	{
		mcFont = C2D_FontLoad("romfs:/mcfont.bcfnt");
		sshs["hearts"] = C2D_SpriteSheetLoad("romfs:/gfx/hearts.t3x");
		sshs["button"] = C2D_SpriteSheetLoad("romfs:/gfx/button.t3x");

		sshs["steve"] = C2D_SpriteSheetLoad("romfs:/gfx/steve.t3x");
		sshs["zombie"] = C2D_SpriteSheetLoad("romfs:/gfx/zombie.t3x");

	}

	void start()
	{

		float heartY = 4;
		float heartScale = 3;
		float totalWidth = hearts.size() * heartScale * 10;
		float startX = (BOTTOM_SCREEN_WIDTH - totalWidth) / 2.0f;  

		for (int i = 0; i < static_cast<int>(hearts.size()); i++) 
		{
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

	void update()
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
           		//printCurrentFood();
           
          	// window::confirm(activeFood)
       		}
	  	}
    
		if(Input::GetKeyDown(KeyCode::R))
  		{
      		if(activeFood < (int)foodLeft.size() - 1)
      		{
          		activeFood += 1;
         	// printCurrentFood();
          	// window::confirm(activeFood);
      		}
  		}

		if(change)
		{
			for(int i = 0; i < static_cast<int>(faceBtns.size());  i++)
			{
				faceBtns[i].changedSelected(0);
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
			}
		}

		for(int i = 0; i < static_cast<int>(faceBtns.size()); i++)
		{
			if(faceBtns[i].checkPressed())
			{

				for(int j = 0; j < static_cast<int>(faceBtns.size());  j++)
				{
					faceBtns[j].changedSelected(0);
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
				}
			}
		}

	}

	void drawTop()
	{
		C2D_DrawSprite(&steveSprite);
		C2D_DrawSprite(&zombieSprite);
	}

	void drawBottom()
	{
		for(int i = 0; i < static_cast<int>(hearts.size()); i++)
			C2D_DrawSprite(&hearts[i]);

		for(int i = 0; i < static_cast<int>(faceBtns.size()); i++)
			faceBtns[i].render();
		enemyHealthLbl.render();
	}	
	
	void unload()
	{
	   for (const auto& pair : sshs) {
			C2D_SpriteSheetFree(pair.second);
    	}
	}

	~GameScene()
	{
		unload();
	}
};