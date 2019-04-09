#include "PCH.h"
#include "main.h"
#include "CommonRenderInterface/CommonRenderInterface.h"
#include "CommonRenderInterface\criCoreInfo.h"
#include "CommonRenderInterface\criContext.h"
#include "Renderer\Renderer.h"
#include "Scene\FScene.h"
#include "Scene\Scene.h"
#include "Core.h"
#include "ThreadPool.h"
#include <iostream>


void CWindow::create(void) {

	m_Hinstance = GetModuleHandle(NULL);

	// создание окна по умолчанию

	// описываем WNDCLASS
	WNDCLASS _windowClass;

	::ZeroMemory(&_windowClass, sizeof(_windowClass));

	_windowClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	_windowClass.lpfnWndProc = (WNDPROC)CWindow::s_update;
	_windowClass.hInstance = GetModuleHandle(NULL);
	_windowClass.lpszClassName = TEXT("Test");

	// регистрируем класс
	if (!RegisterClass(&_windowClass)) {

		MessageBox(0, "Window FAIL", "ERROR", 0);
	}

	// создаём окно

	DWORD	_style = WS_CLIPSIBLINGS | WS_CLIPCHILDREN | WS_OVERLAPPED | WS_VISIBLE;
	DWORD	_exStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;

	m_Hwnd = ::CreateWindowEx(_exStyle,
		TEXT("Test"),
		TEXT("Test"),
		_style,
		0, 0,
		0, 0,
		NULL,
		NULL,
		m_Hinstance,
		NULL);

	// не удалось создать окно
	if (!m_Hwnd) {

		MessageBox(0, "Window FAIL", "ERROR", 0);
	}

	// настройка окна

	// настройка style и exstyle окна

	HWND	_hWndInsertAfter = 0;

	//if ((desc._props_ & WINDOW_DESC::PROPERTIES::TITLE) == WINDOW_DESC::PROPERTIES::TITLE) { 	//else _style &= ~WS_CAPTION;

	_style |= WS_CAPTION;

	_style |= WS_SYSMENU;

	_exStyle |= WS_EX_TOPMOST;
	//_hWndInsertAfter = HWND_TOPMOST;

	// установка style и exstyle
	SetWindowLong(m_Hwnd, GWL_STYLE, _style);
	SetWindowLong(m_Hwnd, GWL_EXSTYLE, _exStyle);

	// настройка координат окна
	RECT _windowCoord = { 0, 0, 800, 600 };
	AdjustWindowRectEx(&_windowCoord, _style, FALSE, _exStyle);
	_windowCoord = { 1000, 100, abs(_windowCoord.left) + abs(_windowCoord.right), abs(_windowCoord.bottom) + abs(_windowCoord.top) };

	//_windowCoord.left = 1000;
	//_windowCoord.top = 100;
	//_windowCoord.right = abs(_windowCoord.left) + abs(_windowCoord.right);
	//_windowCoord.bottom = abs(_windowCoord.bottom) + abs(_windowCoord.top);

	// установка координат окна
	SetWindowPos(m_Hwnd, _hWndInsertAfter, _windowCoord.left, _windowCoord.top, _windowCoord.right, _windowCoord.bottom, 0);

	// установка текста в заголовок
	SetWindowText(m_Hwnd, "FUNRender");

	SetWindowLong(m_Hwnd, GWLP_USERDATA, (LONG_PTR)this);

	m_CenterPosition = vec2i(_windowCoord.left + _windowCoord.right / 2, _windowCoord.top + _windowCoord.bottom / 2);

	SetCursorPos(m_CenterPosition.x, m_CenterPosition.y);
}

LRESULT CWindow::update(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	//VK_ESCAPE
	switch (message) {

	// Изменение положения мыши.
	case WM_MOUSEMOVE: {

		//if (m_Exit) {
			vec2i _currentCoord;
			vec2i _deltaMove;

			POINT _currentCoordScreen;

			_currentCoordScreen.x = GET_X_LPARAM(lParam);
			_currentCoordScreen.y = GET_Y_LPARAM(lParam);

			ClientToScreen(m_Hwnd, &_currentCoordScreen);

			_deltaMove.x = m_CenterPosition.x - _currentCoordScreen.x;
			_deltaMove.y = m_CenterPosition.y - _currentCoordScreen.y;

			if (_deltaMove.x != 0 || _deltaMove.y != 0) {

				WINDOW_SIGNAL_MOVE _newSignal = {};

				_newSignal.m_PositionX = _deltaMove.x;
				_newSignal.m_PositionY = _deltaMove.y;



				SetCursorPos(m_CenterPosition.x, m_CenterPosition.y);

				m_S_MouseMove.emit(&_newSignal);
			}
		//}
	break;

	}
	// Клавиша нажата.
	case WM_KEYDOWN: {

		if (wParam == VK_ESCAPE) { 
			std::exit(2);
			m_Exit = true;
		}

		SIGNAL_WINDOW_KEYBOARD _newSignal;

		_newSignal.m_State = SIGNAL_WINDOW_KEYBOARD::STATE::DOWN;
		_newSignal.m_Key = getKey(wParam);

		m_Keyboard.emit(&_newSignal);

		break;

	}

	case WM_SYSKEYDOWN: {

		SIGNAL_WINDOW_KEYBOARD _newSignal;

		_newSignal.m_State = SIGNAL_WINDOW_KEYBOARD::STATE::DOWN;
		_newSignal.m_Key = getKey(wParam);

		m_Keyboard.emit(&_newSignal);

		break;

	}

	// Клавиша отжата.
	case WM_KEYUP:

		SIGNAL_WINDOW_KEYBOARD _newSignal;

		_newSignal.m_State = SIGNAL_WINDOW_KEYBOARD::STATE::UP;
		_newSignal.m_Key = getKey(wParam);

		m_Keyboard.emit(&_newSignal);

		break;

	case WM_SYSKEYUP: {

		SIGNAL_WINDOW_KEYBOARD _newSignal;

		_newSignal.m_State = SIGNAL_WINDOW_KEYBOARD::STATE::UP;
		_newSignal.m_Key = getKey(wParam);

		m_Keyboard.emit(&_newSignal);

		break;

	break;
	}

	// Изменён размер окна
	case WM_SIZE: {

	break;
	}

	// Все остальные сообщения
	default: {

	return DefWindowProc(hWnd, message, wParam, lParam);
	}

	} // case

	return DefWindowProc(hWnd, message, wParam, lParam);
}

SIGNAL_WINDOW_KEYBOARD::KEY CWindow::getKey(WPARAM wParam) {

	switch (wParam) {

	case 0x41: return SIGNAL_WINDOW_KEYBOARD::KEY::A;	break;
	case 0x42: return SIGNAL_WINDOW_KEYBOARD::KEY::B;	break;
	case 0x43: return SIGNAL_WINDOW_KEYBOARD::KEY::C;	break;
	case 0x44: return SIGNAL_WINDOW_KEYBOARD::KEY::D;	break;
	case 0x45: return SIGNAL_WINDOW_KEYBOARD::KEY::E;	break;
	case 0x46: return SIGNAL_WINDOW_KEYBOARD::KEY::F;	break;
	case 0x47: return SIGNAL_WINDOW_KEYBOARD::KEY::G;	break;
	case 0x48: return SIGNAL_WINDOW_KEYBOARD::KEY::H;	break;
	case 0x49: return SIGNAL_WINDOW_KEYBOARD::KEY::I;	break;
	case 0x4A: return SIGNAL_WINDOW_KEYBOARD::KEY::J;	break;
	case 0x4B: return SIGNAL_WINDOW_KEYBOARD::KEY::K;	break;
	case 0x4C: return SIGNAL_WINDOW_KEYBOARD::KEY::L;	break;
	case 0x4D: return SIGNAL_WINDOW_KEYBOARD::KEY::M;	break;
	case 0x4E: return SIGNAL_WINDOW_KEYBOARD::KEY::N;	break;
	case 0x4F: return SIGNAL_WINDOW_KEYBOARD::KEY::O;	break;
	case 0x50: return SIGNAL_WINDOW_KEYBOARD::KEY::P;	break;
	case 0x51: return SIGNAL_WINDOW_KEYBOARD::KEY::Q;	break;
	case 0x52: return SIGNAL_WINDOW_KEYBOARD::KEY::R;	break;
	case 0x53: return SIGNAL_WINDOW_KEYBOARD::KEY::S;	break;
	case 0x54: return SIGNAL_WINDOW_KEYBOARD::KEY::T;	break;
	case 0x55: return SIGNAL_WINDOW_KEYBOARD::KEY::U;	break;
	case 0x56: return SIGNAL_WINDOW_KEYBOARD::KEY::V;	break;
	case 0x57: return SIGNAL_WINDOW_KEYBOARD::KEY::W;	break;
	case 0x58: return SIGNAL_WINDOW_KEYBOARD::KEY::X;	break;
	case 0x59: return SIGNAL_WINDOW_KEYBOARD::KEY::Y;	break;
	case 0x5A: return SIGNAL_WINDOW_KEYBOARD::KEY::Z;	break;
	}
}
//==============================================================
//==============================================================

bool G_WORK = true;


LRESULT CALLBACK CWindow::s_update(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	CWindow *this_ptr = (CWindow*)GetWindowLongPtr(hWnd, GWLP_USERDATA);

	if (this_ptr == NULL) {
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	else {
		// Call the Message Handler for my class (MsgProc in my case)

		return this_ptr->update(hWnd, message, wParam, lParam);
	}

	
}
void CWindow::update(void) {

	MSG _msg;

	// крутим цикл пока есть события
	while (PeekMessage(&_msg, 0, 0, 0, PM_REMOVE)) {

		TranslateMessage(&_msg);

		DispatchMessage(&_msg);
	}
}

//==============================================================
//==============================================================


void create() {

	

}

//==============================================================
//==============================================================

/*void loadTexture() {

	std::vector<std::string> _nameTexture = {
		"D:/Laboratory/FUNRender/Data/Texture/girl_0.tga",
		"D:/Laboratory/FUNRender/Data/Texture/girl_1.tga",
		"D:/Laboratory/FUNRender/Data/Texture/girl_2.tga",
		"D:/Laboratory/FUNRender/Data/Texture/girl_3.tga",
		"D:/Laboratory/FUNRender/Data/Texture/girl_4.tga",
		"D:/Laboratory/FUNRender/Data/Texture/girl_5.tga",
		"D:/Laboratory/FUNRender/Data/Texture/girl_6.tga",
		"D:/Laboratory/FUNRender/Data/Texture/girl_7.tga",
		"D:/Laboratory/FUNRender/Data/Texture/girl_8.tga",
		"D:/Laboratory/FUNRender/Data/Texture/girl_9.tga",
		"D:/Laboratory/FUNRender/Data/Texture/girl_10.tga"
	};

	size_t _rgbSize = 0;
	size_t _rgbaSize = 0;

	for (const auto &itName : _nameTexture) {

		std::ifstream _stream(itName, std::ios::in | std::ios::binary);

		TGAHeader _tgaHeader;

		// читаем заголовок tga файла
		_stream.read((char*)(&_tgaHeader), sizeof(TGAHeader));

		// размер
		_rgbSize += _tgaHeader._width_ * _tgaHeader._height_ * 3;
		_rgbaSize += _tgaHeader._width_ * _tgaHeader._height_ * 4;

	}

	//std::vector<char> _rgbData(_rgbSize);
	//std::vector<char> _rgbaData(_rgbaSize);
	//_rgbData.resize(_rgbSize);
	//_rgbaData.resize(_rgbaSize);
	//_rgbData.reserve(_rgbSize);
	//_rgbaData.reserve(_rgbaSize);
	char *_rgbData = new char[_rgbSize];
	char *_rgbaData = new char[_rgbaSize];
	uint32_t _rgbOffset = 0;
	uint32_t _rgbaOffset = 0;

	for (const auto &itName : _nameTexture) {

		std::ifstream _stream(itName, std::ios::in | std::ios::binary);

		TGAHeader _tgaHeader;

		// читаем заголовок tga файла
		_stream.read((char*)(&_tgaHeader), sizeof(TGAHeader));

		// размер
		_rgbSize = _tgaHeader._width_ * _tgaHeader._height_ * 3;
		_rgbaSize = _tgaHeader._width_ * _tgaHeader._height_ * 4;

		// читаем
		_stream.read(&_rgbData[_rgbOffset], _rgbSize);

		// форматируем данные (данный код был спизжен с https://github.com/sergeyreznik/et-engine)
		for (size_t i = 0, k = 0; i < _rgbSize; i += 3, k += 4) {

			_rgbData[_rgbOffset + i] ^= _rgbData[_rgbOffset + i + 2];
			_rgbData[_rgbOffset + i + 2] ^= _rgbData[_rgbOffset + i];
			_rgbData[_rgbOffset + i] ^= _rgbData[_rgbOffset + i + 2];

			_rgbaData[_rgbaOffset + k + 0] = _rgbData[_rgbOffset + i + 0];
			_rgbaData[_rgbaOffset + k + 1] = _rgbData[_rgbOffset + i + 1];
			_rgbaData[_rgbaOffset + k + 2] = _rgbData[_rgbOffset + i + 2];
			_rgbaData[_rgbaOffset + k + 3] = 0;
		}

		_rgbOffset += (uint32_t)_rgbSize;
		_rgbaOffset += (uint32_t)_rgbaSize;
	}

	std::cout << "OK";
}*/

//==============================================================
//==============================================================


//==============================================================
//==============================================================

class TestTask : public CTask {

public:

	FE::SCENE::Scene		m_Scene;

	void execute() {

		FE::SCENE::SceneArr _scenes = { m_Scene };
		FE::SCENE::OPERATION::update(&_scenes);
	}
};

int main() {

	/*COORD crd = { 350, 50 };
	SMALL_RECT src = { 0, 0, crd.X, crd.Y };
	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), crd);
	SetConsoleWindowInfo(GetStdHandle(STD_OUTPUT_HANDLE), TRUE, &src);*/

	/*HWND hwnd;
	char Title[1024];
	GetConsoleTitle(Title, 1024); // Узнаем имя окна
	hwnd = FindWindow(NULL, Title); // Узнаем hwnd окна
	MoveWindow(hwnd, 0, 0, 1000, 200, TRUE);//xnew,ynew,wnew,hnew -новые положение x,y, ширина и */

	/*HANDLE out_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD crd = { 450, 50 };
	SMALL_RECT src = { 0, 0, crd.X - 1, crd.Y - 1 };
	SetConsoleWindowInfo(out_handle, true, &src);
	SetConsoleScreenBufferSize(out_handle, crd);*/

	create();

	FE::CORE::Core _coreEngine = new FE::CORE::CCore();

	_coreEngine->create();

	while (true) {
		_coreEngine->update();
	}
	setlocale(LC_ALL, "Russian");
	
	//_coreEngine->execute();

	return 0;
}