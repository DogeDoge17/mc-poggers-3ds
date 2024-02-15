#pragma once
#include <3ds.h>
#include <citro2d.h>
#include <bits/stdc++.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "utils.hpp"

namespace KeyCode{
	enum KeyCodes
	{
		A,
		B,
		Y,
		X,
		L,
		R,
		ZL,
		ZR,
		Up,
		Down,
		Left,
		Right,
		Start,
		Select,
		CUp,
		CDown,
		CLeft,
		CRight,
		Touch
	};
};

namespace AnalogCode{
	enum AnalogCodes
	{
		DHorizontal,
		DVertical,
		PHorizontal,
		PVertical,
		CHorizontal,
		CVertical	
	};
};

namespace RotationDirection{
	enum RotationDirections
	{
		GyroX,
		GyroY,
		GyroZ,
		AccelerX,
		AccelerY,
		AccelerZ,
	};
};


struct TouchInfo{
	touchPosition pos;
	bool validTouch;
};

bool INP_touchDown = false;
bool INP_touchDownR = true;
bool INP_touchUpR = true;
bool INP_touchUp = false;

//wrapper class for the built-in input system because im a stupid unity user
class Input
{
private:
	static constexpr float m_deadZone = 0.2f; 

public:
	static bool GetKeyDown(KeyCode::KeyCodes code)
	{
		u32 c_keysDown = hidKeysDown();

		switch(code)
		{
		case KeyCode::A: return c_keysDown & KEY_A; break;
		case KeyCode::B: return c_keysDown & KEY_B; break;
		case KeyCode::Y: return c_keysDown & KEY_Y; break;
		case KeyCode::X: return c_keysDown & KEY_X; break;

		case KeyCode::L: return c_keysDown & KEY_L; break;
		case KeyCode::R: return c_keysDown & KEY_R; break;

		case KeyCode::ZL: return c_keysDown & KEY_ZL; break;
		case KeyCode::ZR: return c_keysDown & KEY_ZR; break;

		case KeyCode::Start: return c_keysDown & KEY_START; break;
		case KeyCode::Select: return c_keysDown & KEY_SELECT; break;

		case KeyCode::Up: return c_keysDown & KEY_DUP; break;
		case KeyCode::Down: return c_keysDown & KEY_DDOWN; break;
		case KeyCode::Left: return c_keysDown & KEY_DLEFT; break;
		case KeyCode::Right: return c_keysDown & KEY_DRIGHT; break;

		case KeyCode::CUp: return c_keysDown & KEY_CSTICK_UP; break;
		case KeyCode::CDown: return c_keysDown & KEY_CSTICK_DOWN; break;
		case KeyCode::CLeft: return c_keysDown & KEY_CSTICK_LEFT; break;
		case KeyCode::CRight: return c_keysDown & KEY_CSTICK_RIGHT; break;

		case KeyCode::Touch: return c_keysDown & KEY_TOUCH; break;
		}

		return false;
	}

	static bool GetKeyUp(KeyCode::KeyCodes code)
	{
		u32 c_keysUp = hidKeysHeld();

		switch(code)
		{
		case KeyCode::A: return c_keysUp & KEY_A; break;
		case KeyCode::B: return c_keysUp & KEY_B; break;
		case KeyCode::Y: return c_keysUp & KEY_Y; break;
		case KeyCode::X: return c_keysUp & KEY_X; break;

		case KeyCode::L: return c_keysUp & KEY_L; break;
		case KeyCode::R: return c_keysUp & KEY_R; break;

		case KeyCode::ZL: return c_keysUp & KEY_ZL; break;
		case KeyCode::ZR: return c_keysUp & KEY_ZR; break;

		case KeyCode::Start: return c_keysUp & KEY_START; break;
		case KeyCode::Select: return c_keysUp & KEY_SELECT; break;

		case KeyCode::Up: return c_keysUp & KEY_DUP; break;
		case KeyCode::Down: return c_keysUp & KEY_DDOWN; break;
		case KeyCode::Left: return c_keysUp & KEY_DLEFT; break;
		case KeyCode::Right: return c_keysUp & KEY_DRIGHT; break;

		case KeyCode::CUp: return c_keysUp & KEY_CSTICK_UP; break;
		case KeyCode::CDown: return c_keysUp & KEY_CSTICK_DOWN; break;
		case KeyCode::CLeft: return c_keysUp & KEY_CSTICK_LEFT; break;
		case KeyCode::CRight: return c_keysUp & KEY_CSTICK_RIGHT; break;
			
		case KeyCode::Touch: return c_keysUp & KEY_TOUCH; break;
		}

		return false;
	}

	static bool GetKey(KeyCode::KeyCodes code)
	{
		u32 c_keysHeld = hidKeysHeld();

		switch(code)
		{
		case KeyCode::A: return c_keysHeld & KEY_A; break;
		case KeyCode::B: return c_keysHeld & KEY_B; break;
		case KeyCode::Y: return c_keysHeld & KEY_Y; break;
		case KeyCode::X: return c_keysHeld & KEY_X; break;

		case KeyCode::L: return c_keysHeld & KEY_L; break;
		case KeyCode::R: return c_keysHeld & KEY_R; break;

		case KeyCode::ZL: return c_keysHeld & KEY_ZL; break;
		case KeyCode::ZR: return c_keysHeld & KEY_ZR; break;

		case KeyCode::Start: return c_keysHeld & KEY_START; break;
		case KeyCode::Select: return c_keysHeld & KEY_SELECT; break;

		case KeyCode::Up: return c_keysHeld & KEY_DUP; break;
		case KeyCode::Down: return c_keysHeld & KEY_DDOWN; break;
		case KeyCode::Left: return c_keysHeld & KEY_DLEFT; break;
		case KeyCode::Right: return c_keysHeld & KEY_DRIGHT; break;

		case KeyCode::CUp: return c_keysHeld & KEY_CSTICK_UP; break;
		case KeyCode::CDown: return c_keysHeld & KEY_CSTICK_DOWN; break;
		case KeyCode::CLeft: return c_keysHeld & KEY_CSTICK_LEFT; break;
		case KeyCode::CRight: return c_keysHeld & KEY_CSTICK_RIGHT; break;

		case KeyCode::Touch: return c_keysHeld & KEY_TOUCH; break;
		}

		return false;
	}

	//Applies a deadzone i dont really remember what the original method does so it will do this
	static float GetAxisRaw(AnalogCode::AnalogCodes code)
	{
		switch(code)
		{
		case AnalogCode::PHorizontal: circlePosition posH; hidCircleRead(&posH); return clamp((float)posH.dx / 154,-1,1); break;
		case AnalogCode::PVertical: circlePosition posV; hidCircleRead(&posV); return clamp((float)posV.dy/ 154,-1,1); break;

		case AnalogCode::DHorizontal: if(Input::GetKey(KeyCode::Left)) return -1; else if(Input::GetKey(KeyCode::Right)) return 1; else return 0; break;
		case AnalogCode::DVertical: if(Input::GetKey(KeyCode::Down)) return -1; else if(Input::GetKey(KeyCode::Up)) return 1; else return 0; break;

		case AnalogCode::CHorizontal: if(Input::GetKey(KeyCode::CDown)) return -1; else if(Input::GetKey(KeyCode::CUp)) return 1; else return 0; break;
		case AnalogCode::CVertical: if(Input::GetKey(KeyCode::CLeft)) return -1; else if(Input::GetKey(KeyCode::CRight)) return 1; else return 0; break;
		}
		return 0;
	}


	static void Update(){
		touchPosition touch;
		hidTouchRead(&touch);
	    
	    if (touch.px > 0 || touch.py > 0)
        {
        	INP_touchUpR = false;
        	if(INP_touchDownR){
            	INP_touchDown = true;
            	INP_touchUp = false;
            	INP_touchDownR = false;
            }else
            	INP_touchDown = false;

        }
        if (touch.px == 0 && touch.py == 0)
        {
        	if(INP_touchUpR)
        		INP_touchUp = false;

            if (INP_touchDown == true)
            {
                INP_touchDown = false;
                INP_touchUp = true;
                INP_touchUpR = true;
            }
            INP_touchDownR = true;
        }

	}

	
	static TouchInfo GetTouch()
	{
		TouchInfo touchInfo;
		hidTouchRead(&touchInfo.pos);
		touchInfo.validTouch = touchInfo.pos.px != 0 || touchInfo.pos.py != 0;
		return touchInfo;
	}

	static TouchInfo GetTouchDown()
	{
		TouchInfo touchInfo;
		hidTouchRead(&touchInfo.pos);
		touchInfo.validTouch = INP_touchDown;
		return touchInfo;
	}

	static TouchInfo GetTouchUp()
	{
		TouchInfo touchInfo;
		hidTouchRead(&touchInfo.pos);
		touchInfo.validTouch = INP_touchUp;
		return touchInfo;
	}



	#pragma GCC diagnostic ignored "-Wswitch" //i think this is help optimize but idk
	static float GetAxis(AnalogCode::AnalogCodes code)
	{
		switch(code)
		{

		case AnalogCode::PHorizontal:
			{
				circlePosition posH;
				hidCircleRead(&posH);
				float val = (float)posH.dx / 154;
				if(positive(val) > m_deadZone)
					return clamp(val,-1,1);
				else
					return 0;
			}
			break;
		case AnalogCode::PVertical:
			{
				circlePosition posV;
				hidCircleRead(&posV);
				float val = (float)posV.dy / 154;
				if(positive(val) > m_deadZone)
					return clamp(val,-1,1);
				else
					return 0;
			}
			break;
		}
		return GetAxisRaw(code);
	}
};