#pragma once
#define Menu_Click_New		1
#define Menu_Click_			2
#define Menu_Click_			3
#define Menu_Click_Exit		4
#define IDB_Button1			5

#define Difficulty_SE		6
#define Difficulty_E		7
#define Difficulty_M		8
#define Difficulty_H		9
#define Difficulty_SH		10
#define Difficulty_L		11
#define About_me			12


HWND hwnd_buttonEndInput[16][16] = {};
HWND hWnd_result;
HWND hWnd_time;

class KWnd {
public:
	KWnd(LPCTSTR windowName, HINSTANCE hInst, int cmdShow,
		LRESULT(WINAPI* pWndProc)(HWND, UINT, WPARAM, LPARAM),
		LPCTSTR menuName = NULL,
		int x = CW_USEDEFAULT, int y = 0,     
		int width = CW_USEDEFAULT, int height = 0,
		UINT classStyle = CS_HREDRAW | CS_VREDRAW,
		DWORD windowStyle = WS_OVERLAPPED | WS_MINIMIZEBOX | WS_SYSMENU,
		HWND hParent = NULL);
	HWND GetHWnd() { return hWnd; }

protected:
	HWND hWnd;
	WNDCLASSEX wc;
};



LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
void full_table(HDC hDC, HWND hWnd);
void full_buttons(HWND hWnd, HINSTANCE hInst);
void buttom_bomb(HWND hWnd, HINSTANCE hInst, int x0, int y0, int x1, int y1, int i, int j);
void paint_pic(HDC hDC, int x0, int y0, int x1, int y1);
void New_game(HWND hWnd);
void open_buttoms(int i, int j);
void paint_tables(HDC hDC, HWND hWnd);


void paint_pic(HDC hDC, int x0, int y0, int x1, int y1)
{
	HBITMAP hBmp = (HBITMAP)LoadImage(NULL, L"temp\\3.bmp",
		IMAGE_BITMAP, 0,
		0, LR_LOADFROMFILE);
	HBRUSH hBrush = CreatePatternBrush(hBmp);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, x0, y0, x1, y1);
	DeleteObject(SelectObject(hDC, hOldBrush));
	return;
};

void paint_Bomb(HDC hDC, int x0, int y0, int x1, int y1)
{
	HBITMAP hBmp = (HBITMAP)LoadImage(NULL, L"temp\\1.bmp",
		IMAGE_BITMAP, 0,
		0, LR_LOADFROMFILE);
	HBRUSH hBrush = CreatePatternBrush(hBmp);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, x0, y0, x1, y1);
	DeleteObject(SelectObject(hDC, hOldBrush));
	return;
};

void paint_NULL(HDC hDC, int x0, int y0, int x1, int y1)
{
	const COLORREF rgbRed = 0x00c26ec0;
	HBRUSH hhh = CreateSolidBrush(rgbRed);
	HBRUSH hh3 = (HBRUSH)SelectObject(hDC, hhh);
	Rectangle(hDC, x0, y0, x1, y1);
	DeleteObject(SelectObject(hDC, hhh));
	return;
};


void paint_NULL_up(HDC hDC)
{
	const COLORREF rgbRed = 0x00c26ec0;
	HBRUSH hhh = CreateSolidBrush(rgbRed);
	HBRUSH hh3 = (HBRUSH)SelectObject(hDC, hhh);
	Rectangle(hDC, 375, 10, 475, 44);
	Rectangle(hDC, 100, 10, 200, 44);
	HBITMAP hBmp = (HBITMAP)LoadImage(NULL, L"temp\\1.bmp",
		IMAGE_BITMAP, 0,
		0, LR_LOADFROMFILE);
	HBRUSH hBrush = CreatePatternBrush(hBmp);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);
	Rectangle(hDC, 160, 576, 192, 609);
	Rectangle(hDC, 384, 576, 416, 609);
	DeleteObject(SelectObject(hDC, hhh));
	return;
};


void paint_N1(HDC hDC, int x0, int y0, int x1, int y1, int k)
{
	RECT rect;
	
	COLORREF rgb_1 = 0x00dbb1de;
	HBRUSH hhh = CreateSolidBrush(rgb_1);
	HBRUSH hh3;

	hh3 = (HBRUSH)SelectObject(hDC, hhh); Rectangle(hDC, x0, y0, x1, y1);  DeleteObject(SelectObject(hDC, hhh));

	rect.left = x0;
	rect.top = y0;
	rect.right = x1;
	rect.bottom = y1;

	switch (k)
	{
	case 1: 	SetTextColor(hDC, RGB(151, 91, 212)); DrawText(hDC, L"1", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); break;
	case 2: 	SetTextColor(hDC, RGB(8, 0, 153)); DrawText(hDC, L"2", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); break;
	case 3: 	SetTextColor(hDC, RGB(212, 91, 181)); DrawText(hDC, L"3", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); break;
	case 4: 	SetTextColor(hDC, RGB(207, 48, 48)); DrawText(hDC, L"4", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); break;
	case 5: 	SetTextColor(hDC, RGB(255, 255, 255)); DrawText(hDC, L"5", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); break;
	case 6: 	SetTextColor(hDC, RGB(125, 21, 91)); DrawText(hDC, L"6", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); break;
	case 7: 	SetTextColor(hDC, RGB(40, 155, 155)); DrawText(hDC, L"7", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); break;
	case 8: 	SetTextColor(hDC, RGB(0, 0, 0)); DrawText(hDC, L"8", -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER); break;

	default:
		break;
	}


	SetTextColor(hDC, RGB(0, 0, 0));
	return;
};

void paint_letters(HDC hDC)
{
	RECT rect;

	
	rect.left = 0;
	rect.top = 575;
	rect.right = 580;
	rect.bottom = 600;

	DrawText(hDC, L"SAPPER ", -1, &rect,
		DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		
	rect.left = 0;
	rect.top = 590;
	rect.right = 580;
	rect.bottom = 620;

	DrawText(hDC, L"Especially for POLYANA", -1, &rect,
		DT_SINGLELINE | DT_CENTER | DT_VCENTER);
	return;

}

void Menu_main(HWND hWnd)
{
	HMENU RootMenu = CreateMenu();
	HMENU ChildMenu = CreateMenu();
	HMENU ChildMenu_setGame = CreateMenu();

	AppendMenu(RootMenu, MF_POPUP, (UINT_PTR)ChildMenu, L"Game");
	AppendMenu(ChildMenu, MF_STRING, Menu_Click_New, L"New");

	AppendMenu(ChildMenu, MF_POPUP, (UINT_PTR)ChildMenu_setGame,	L"Difficulty");
	AppendMenu(ChildMenu_setGame, MF_POPUP, Difficulty_SE,			L"Super Easy   - 15 Bombs");
	AppendMenu(ChildMenu_setGame, MF_POPUP, Difficulty_E,			L"Easy              - 45 Bombs");
	AppendMenu(ChildMenu_setGame, MF_POPUP, Difficulty_M,			L"Medium      - 60 Bombs");
	AppendMenu(ChildMenu_setGame, MF_POPUP, Difficulty_H,			L"Hard             - 90 Bombs");
	AppendMenu(ChildMenu_setGame, MF_POPUP, Difficulty_SH,			L"Super Hard  - 140 Bombs");
	AppendMenu(ChildMenu_setGame, MF_POPUP, Difficulty_L,			L"Legendary    - 200 Bombs");
	
	AppendMenu(ChildMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(ChildMenu, MF_STRING, About_me, L"About");

	AppendMenu(RootMenu, MF_STRING, Menu_Click_Exit, L"Exit");

	SetMenu(hWnd, RootMenu);
	return;

}

void buttom_bomb(HWND hWnd, HINSTANCE hInst, int x0, int y0, int x1, int y1, int i, int j)
{
	hwnd_buttonEndInput[i][j]  = CreateWindow(L"BUTTON", L" ", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, x0, y0, x1, y1, hWnd, (HMENU)(200+i*16+j), hInst, NULL);
	return;
}



