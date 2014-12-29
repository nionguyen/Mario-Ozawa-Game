
#include "Timer.h"
#include "Game.h"
#include "ResourceManager.h"
#include "ZoomSence.h"

//----------------------------------------------------------------------------------------
void Game::_SetScreenDimension(int Mode)
{
	switch (Mode)
	{
	case GL_RESOLUTION_640_480_24:
		GL_Width = 640;
		GL_Height = 480;

		GL_WndSize.top = 0;
		GL_WndSize.left = 0;
		GL_WndSize.right = 640;
		GL_WndSize.bottom = 480;

		GL_GameDepth = 24;
		GL_BackBufferFormat = D3DFMT_X8R8G8B8;
		break;

	case GL_RESOLUTION_800_600_24:
		GL_Width = 800; 
		GL_Height = 600;
		
		GL_WndSize.top = 0;
		GL_WndSize.left = 0;
		GL_WndSize.right = 800;
		GL_WndSize.bottom = 600;

		GL_GameDepth = 24;
		GL_BackBufferFormat = D3DFMT_X8R8G8B8;
		break;

	case GL_RESOLUTION_1024_768_24:
		GL_Width = 1024; 
		GL_Height = 768;

		GL_WndSize.top = 0;
		GL_WndSize.left = 0;
		GL_WndSize.right = 1024;
		GL_WndSize.bottom = 768;

		GL_GameDepth = 24;
		GL_BackBufferFormat = D3DFMT_X8R8G8B8;
		break;

	default: 
		break;
	}
}

void ResetDevice()
{
	if(GLDevice)
	{
		GLSpriteHandler->OnLostDevice();

		GLDevice->Reset(&GLPresentPara);

		GLSpriteHandler->OnResetDevice();
	}
}

bool ValidateDevice()
{
	HRESULT hResult = NULL;
	hResult = GLDevice->TestCooperativeLevel();

	if (FAILED(hResult))
	{
		if (hResult == D3DERR_DEVICELOST)
			return false;

		if (hResult == D3DERR_DEVICENOTRESET)
		{
			GLSpriteHandler->OnLostDevice();

			//re-create GLPresentPara
			ZeroMemory( &GLPresentPara, sizeof(GLPresentPara) );
			GLPresentPara.Windowed = GL_IsFullScreen ? FALSE : TRUE;
			GLPresentPara.SwapEffect = D3DSWAPEFFECT_DISCARD;
			GLPresentPara.BackBufferFormat = GL_BackBufferFormat; 
			GLPresentPara.BackBufferCount = 1;
			GLPresentPara.BackBufferHeight = GL_Height;
			GLPresentPara.BackBufferWidth = GL_Width;
			//

			if (FAILED(GLDevice->Reset(&GLPresentPara)))
			{
				//DestroyWindow(GL_HWND);
				//return false;
			}
			GLSpriteHandler->OnResetDevice();
		}
	}
	return true;
}

LRESULT CALLBACK Game::_WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) 
	{
	case WM_ACTIVATE:
		{
			if(GLKeyBoard != NULL){
				GLKeyBoard->Acquire();
			}

			//if(wParam && GLDevice != NULL)
			//	ValidateDevice();
		} break;

	case WM_DESTROY: 
		//GLMessage("Destroy app!");
		PostQuitMessage(0);
		break;

	default: 
		return DefWindowProc(hWnd, message, wParam,lParam);
	}

	return 0;
}

void Game::_InitWindow()
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = GL_HINSTANCE;

	wc.lpfnWndProc = (WNDPROC) Game::_WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = GL_GameName;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	DWORD style; 
	if (GL_IsFullScreen)
		style = WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP;
	else 
		style = WS_VISIBLE | WS_SYSMENU | WS_MINIMIZEBOX | WS_DLGFRAME; //WS_OVERLAPPEDWINDOW;

	GL_HWND = 
		CreateWindow(
		GL_GameName,
		GL_GameName,
		style, 
		CW_USEDEFAULT,
		CW_USEDEFAULT, 
		GL_Width,
		GL_Height,
		NULL,
		NULL,
		GL_HINSTANCE,
		NULL);

	if (!GL_HWND) 
	{ 
		GLMessage("Error Init Wnd");
		GLTrace("[ERROR] Failed to created window!");
		DWORD ErrCode = GetLastError();
	}

	ShowWindow(GL_HWND,SW_SHOWNORMAL);
	UpdateWindow(GL_HWND);
}

void Game::_InitDirectX()
{
	GLDirect = Direct3DCreate9(D3D_SDK_VERSION);

	ZeroMemory( &GLPresentPara, sizeof(GLPresentPara) );

	GLPresentPara.Windowed = GL_IsFullScreen ? FALSE : TRUE;

	GLPresentPara.SwapEffect = D3DSWAPEFFECT_DISCARD;

	GLPresentPara.BackBufferFormat = GL_BackBufferFormat; 
	GLPresentPara.BackBufferCount = 1;
	GLPresentPara.BackBufferHeight = GL_Height;
	GLPresentPara.BackBufferWidth = GL_Width;

	GLDirect->CreateDevice(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		GL_HWND,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&GLPresentPara,
		&GLDevice);

	if (GLDevice == NULL) 
	{
		GLMessage("Error");
		GLTrace("Can not create device!", "Game.h");
	}

	GLDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &GLBackBuffer);

	HRESULT res = D3DXCreateSprite(GLDevice, &GLSpriteHandler);
	
	//set bool
	GL_IsInitedDX = true;
}

void Game::_InitKeyboard()
{
	HRESULT hr = DirectInput8Create
		( 
			GL_HINSTANCE, 
			DIRECTINPUT_VERSION, 
			IID_IDirectInput8, (VOID**)&GLDirectInput, NULL 
		);

	// TO-DO: put in exception handling
	if (hr != DI_OK) return;

	GLTrace("DirectInput has been created");

	hr = GLDirectInput->CreateDevice(GUID_SysKeyboard, &GLKeyBoard, NULL); 

	// TO-DO: put in exception handling
	if (hr != DI_OK) return;

	GLTrace("DirectInput keyboard has been created");

	// Set the data format to "keyboard format" - a predefined data format 
	//
	// A data format specifies which controls on a device we
	// are interested in, and how they should be reported.
	//
	// This tells DirectInput that we will be passing an array
	// of 256 bytes to IDirectInputDevice::GetDeviceState.

	hr = GLKeyBoard->SetDataFormat(&c_dfDIKeyboard);

	GLTrace("SetDataFormat for keyboard successfully");

	hr = GLKeyBoard->SetCooperativeLevel(GL_HWND, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE); 

	GLTrace("SetCooperativeLevel for keyboard successfully");

	// IMPORTANT STEP TO USE BUFFERED DEVICE DATA!
	//
	// DirectInput uses unbuffered I/O (buffer size = 0) by default.
	// If you want to read buffered data, you need to set a nonzero
	// buffer size.
	//
	// Set the buffer size to DINPUT_BUFFERSIZE (defined above) elements.
	//
	// The buffer size is a DWORD property associated with the device.
	DIPROPDWORD dipdw;

	dipdw.diph.dwSize       = sizeof(DIPROPDWORD);
	dipdw.diph.dwHeaderSize = sizeof(DIPROPHEADER);
	dipdw.diph.dwObj        = 0;
	dipdw.diph.dwHow        = DIPH_DEVICE;
	dipdw.dwData            = GL_KEY_BUFFER_SIZE; // Arbitrary buffer size

	GLTrace("SetProperty for keyboard successfully");

	hr = GLKeyBoard->SetProperty( DIPROP_BUFFERSIZE, &dipdw.diph );
	if (hr != DI_OK) return;

	hr = GLKeyBoard->Acquire(); 
	if (hr != DI_OK) return;

	GLTrace("Keyboard has been acquired successfully");
}

void Game::_RenderFrame()
{
	if (GLDevice->BeginScene()) 
	{
		GLDevice->ColorFill(GLBackBuffer, NULL, D3DCOLOR_XRGB(0, 0, 0));
		
		//mac dinh chay truoc khi cac sence duoc chay
		//before
		RenderFrame(_DeltaTime);

		//update timer
		MyTimer::Update();

		//
		if(!_listSence.empty()){
			int size = _listSence.size();
			ISence* sence;

			for(int i = 0; i < size; ++i){
				sence = _listSence[i];

				if(sence != NULL){
					sence->UpdateRender(_DeltaTime);
				}
			}

			for(int i = 0; i < size; ++i){
				sence = _listSence[i];

				if(sence->IsDead()){
					_listSence.erase(_listSence.begin() + i);
					break;
				}
			}
			
		}

		//render after
		RenderFrameAfter(_DeltaTime);

		//
		GLDevice->EndScene();
	}

	GLDevice->Present(NULL,NULL,NULL,NULL);
}

void Game::_ProcessKeyBoard()
{
	// Collect all key states first
	GLKeyBoard->GetDeviceState( sizeof(_KeyStates), _KeyStates);

	//----------------------------------------- EXIT ---------------------------
	if (IsKeyDown(DIK_ESCAPE)) 
	{
	}

	//------------------------------------------ IN Game -----------------------
	// Collect all buffered events
	DWORD dwElements = GL_KEY_BUFFER_SIZE;
	HRESULT hr = GLKeyBoard->GetDeviceData( sizeof(DIDEVICEOBJECTDATA), _KeyEvents, &dwElements, 0 );

	// Scan through all data, check if the key is pressed or released
	for( DWORD i = 0; i < dwElements; i++ ) 
	{
		int KeyCode = _KeyEvents[i].dwOfs;
		int KeyState = _KeyEvents[i].dwData;

		if ( (KeyState & 0x80) > 0){
			//mac dinh chay truoc khi chay cac sence
			OnKeyDown(KeyCode);

			if(!_listSence.empty()){
				ISence *sence = _listSence.back();
				if(sence != NULL){
					sence->OnKeyDown(KeyCode);
				}
			}
		}
		else {
			//mac dinh chay truoc khi chay cac sence
			OnKeyUp(KeyCode);

			if(!_listSence.empty()){
				ISence *sence = _listSence.back();
				if(sence != NULL){
					sence->OnKeyUp(KeyCode);
				}
			}
		}
	}
}

void Game::_ProcessInput(){
	//mac dinh chay truoc ham cua cac sence
	ProcessInput(_DeltaTime);

	//ProcessInput _listSences
	if(!_listSence.empty()){
		ISence *sence = _listSence.back();
		if(sence != NULL){
			sence->ProcessInput();
		}
	}
}

void Game::_LoadResources(){

	ResourceMng::GetInst();
	
	//load resource for all sence in _listSence
	if(!_listSence.empty()){
		int size = _listSence.size();
		ISence* sence;

		for(int i = 0; i < size; ++i){
			sence = _listSence[i];

			if(sence != NULL){
				sence->Load();
			}
		}
	}

	// always before load for all sence
	LoadResources();	
}

//------ virtual function will be overwrite in sub

void Game::OnKeyUp(int KeyCode) { }

void Game::OnKeyDown(int KeyCode) { }

void Game::RenderFrame(int Delta) { }

void Game::RenderFrameAfter(int Delta) { }

void Game::LoadResources() { }

void Game::ProcessInput(int Delta) { }

//end------ virtual function

//---------------------------------------------public ------------------------------------

Game::Game(HINSTANCE hInstance, char* Name, int Mode, int IsFullScreen, int FrameRate)
{
	GLDirect = NULL;
	GLDevice = NULL;
	GLBackBuffer = NULL;

	GLDirectInput = NULL;
	GLKeyBoard = NULL;

	GL_ColorMode = Mode;
	_SetScreenDimension(Mode);
	GL_GameName = Name;
	GL_IsFullScreen = IsFullScreen;
	GL_FrameRate = FrameRate;

	GL_HINSTANCE = hInstance;
}

Game::~Game()
{
	this->Release();
}

void Game::Release()
{
	if (GLDevice != NULL) GLDevice->Release();
	if (GLDirect != NULL) GLDirect->Release();

	if( GLKeyBoard )
	{
		GLKeyBoard->Unacquire();
		GLKeyBoard->Release();
	}

	if (GLDirectInput) GLDirectInput->Release();

	if(GLBackBuffer != NULL) GLBackBuffer->Release();

	if(GLSpriteHandler != NULL) GLSpriteHandler->Release();

	if(! _listSence.empty()) _listSence.clear();

	ResourceMng::GetInst()->Release();
}

void Game::Init()
{
	_InitWindow();
	_InitDirectX();
	_InitKeyboard();
	_LoadResources();
}

// Main game message loop
void Game::Run()
{
	MSG msg;
	int done = 0;
	
	DWORD tick_per_frame = 100 / GL_FrameRate;
	
	GLTrace(">>> Main game loop has been started");
	
	DWORD frame_start = GetTickCount();

	while (!done) 
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done=1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);			
		}

		DWORD now = GetTickCount();

		_DeltaTime = now - frame_start; 

		if (_DeltaTime >= tick_per_frame)
		{
		
			//nhan 1 lan
			_ProcessKeyBoard();

			//nhan va giu
			_ProcessInput();

			frame_start = now;
			_RenderFrame();
		}

	}

	GLTrace("Main game loop has ended");
}
	
int Game::IsKeyDown(int KeyCode)
{
	return (_KeyStates[KeyCode] & 0x80) > 0;
}

void Game::AddSence(ISence* sence)
{
	_listSence.push_back(sence);

	sence->Load();
}

float Game::GetFPS(){
	if(_DeltaTime != 0)
		return (1000 / _DeltaTime);
	else
		return 0;
}