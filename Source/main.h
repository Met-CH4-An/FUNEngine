#pragma once

#include <Windows.h>
#include <Windowsx.h>
#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>

//#include "ThreadPool.h"
#include "Common/Observer.h"
#include <vector>
#include <map>
#include "Maths/maths.h"
#include "Input/Keyboard.h"
#include "Input/Mouse.h"



struct SIGNAL_WINDOW_KEYBOARD {
	
	enum class KEY {

		A,
		B,
		C,
		D,
		E,
		F,
		G,
		H,
		I,
		J,
		K,
		L,
		M,
		N,
		O,
		P,
		Q,
		R,
		S,
		T,
		U,
		V,
		W,
		X,
		Y,
		Z
		
	};

	enum class STATE {

		UP,
		DOWN,
		PRESS
	};

	KEY			m_Key;
	STATE		m_State;

};

struct WINDOW_SIGNAL_MOVE {

	uint32_t		m_PositionX;
	uint32_t		m_PositionY;
};

class CWindow {

public:

	HWND				m_Hwnd;
	HINSTANCE			m_Hinstance;

	void create(void);

	LRESULT update(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK s_update(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	Signal<const SIGNAL_WINDOW_KEYBOARD*> m_Keyboard;
	Signal<const WINDOW_SIGNAL_MOVE*> m_S_MouseMove;

	void update(void);

	SIGNAL_WINDOW_KEYBOARD::KEY getKey(WPARAM wParam);

	vec2i	m_CenterPosition;

	bool m_Exit = false;
};







