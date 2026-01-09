#pragma once
#include <3ds.h>
#include <citro2d.h>
#include <bits/stdc++.h>
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

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

extern bool INP_touchDown;
extern bool INP_touchDownR;
extern bool INP_touchUpR;
extern bool INP_touchUp;

double clamp(double value, double min, double max);
double positive(double numb);
double negative(double numb);

class Input
{
private:
	static constexpr float m_deadZone = 0.2f; 

public:
	static bool GetKeyDown(KeyCode::KeyCodes code);
	static bool GetKeyUp(KeyCode::KeyCodes code);
	static bool GetKey(KeyCode::KeyCodes code);
	static float GetAxisRaw(AnalogCode::AnalogCodes code);
	static void Update();
	static TouchInfo GetTouch();
	static TouchInfo GetTouchDown();
	static TouchInfo GetTouchUp();
	static float GetAxis(AnalogCode::AnalogCodes code);
};
