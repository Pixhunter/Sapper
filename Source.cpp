#include <windows.h>
#pragma warning(disable: 4996)
#include "resource.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <tchar.h >
#include <chrono> 
#include <shellapi.h>

using namespace std;

const int size_of_war = 16;
int width, height;

int Bomb_number = 35;
int timing = 0;
int game_result = 0;
int first_touch = 0;
int game_von_mode = size_of_war * size_of_war;
int Bomb_number_els = 0;
int Game_mode = 16;
int IDT_TIMER1 = 9;


char mine_war[size_of_war][size_of_war] = {};

HDC hDC;
HINSTANCE hInst;



KWnd::KWnd(LPCTSTR windowName, HINSTANCE hInst, int cmdShow,
	LRESULT(WINAPI* pWndProc)(HWND, UINT, WPARAM, LPARAM),
	LPCTSTR menuName, int x, int y, int width, int height,
	UINT classStyle, DWORD windowStyle, HWND hParent)
{

	FILE* _frp = freopen("CONOUT$", "w", stdout);



	char szClassName[] = "KWndClass";
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = pWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = menuName;
	wc.lpszClassName = L"KWndClass";
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	 
	if (!RegisterClassEx(&wc)) {
		char msg[100] = "Cannot register class: ";
		strcat((char*)msg, (char*)szClassName);
		MessageBox(NULL, L"Cannot register class: ", L"Error", MB_OK);
		return;
	}
	 
	hWnd = CreateWindow(L"KWndClass", windowName, windowStyle,
		x, y, width, height, hParent, (HMENU)NULL, hInst, NULL);

	if (!hWnd) {
		char text[100] = "Cannot create window: ";
		strcat(text, (const char*)windowName);
		MessageBox(NULL, L"Cannot register window: ", L"Error", MB_OK);
		return; 
	}
 


	hInst = (HINSTANCE)GetClassLong(hWnd, GCL_HMODULE);

	ShowWindow(hWnd, cmdShow);
}




//====================================================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int
	nCmdShow)
{
	MSG msg;
	
	KWnd mainWnd(L"Polyana's SAPPER", hInstance, nCmdShow, WndProc, NULL, 600,
		200, 590, 680);
	//KWnd mainWnd(L"Polyana's SAPPER", hInstance, nCmdShow, WndProc);

	

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}



//====================================================================
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	RECT rect_2 = { 430, 10, 590, 390 };
	PAINTSTRUCT ps;
	POINT pt;

	

	int userReply;
	switch (uMsg)
	{

	case WM_COMMAND:
	{
		for (int i = 0; i < size_of_war; i++)
		{
			for (int j = 0; j < size_of_war; j++)
			{
				if (LOWORD(wParam) == (200 + i * 16 + j))
				{
					if ((first_touch == 0) and (mine_war[i][j] == 9)) { goto RESET; }
					first_touch = 1;
					
					SendMessage(hwnd_buttonEndInput[i][j], WM_CLOSE, 0, 0);

					if (mine_war[i][j] == 9) 
					{
						int msgboxID = MessageBox(hWnd, L"You Loose.. \nStart Again?", L"GAME OVER", MB_ICONEXCLAMATION | MB_YESNO);
						if (msgboxID == IDYES)
						{
							goto RESET;
						}
						else
						{
							for (int i = 0; i < size_of_war; i++)
							{
								for (int j = 0; j < size_of_war; j++)
								{
									mine_war[i][j] = NULL;
									if (hwnd_buttonEndInput[i][j])
										SendMessage(hwnd_buttonEndInput[i][j], WM_CLOSE, 0, 0);
								}
							}
							InvalidateRect(hWnd, NULL, TRUE);
						}
					}
					else
					{
						if (mine_war[i][j] == 0) { open_buttoms(i, j); }
						else {
							game_von_mode--;
							game_result += mine_war[i][j] * 15;
							TCHAR p[17];
							_itot(game_result, p, 10);
							SetWindowText(hWnd_result, p);
							_itot(game_result / 15, p, 10);
							SetWindowText(hWnd_time, p);
						}
					}

					if (game_von_mode <= ((Bomb_number - Bomb_number_els)))
					{
						int msgboxID = MessageBox(hWnd, L"You Won!!.. \nStart Again?", L"WIN THE GAME", MB_ICONEXCLAMATION | MB_YESNO);
						if (msgboxID == IDYES)
						{
							goto RESET;
						}
					}	
				}
			}	
		}
		
		switch (wParam)
		{
		case Menu_Click_New:
	
RESET:		
			game_result = 0;
			New_game(hWnd); 
			SetWindowText(hWnd_result, L" 0 ");
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		
		case Difficulty_SE: Bomb_number = 15; game_result = 0; New_game(hWnd); SetWindowText(hWnd_result, L" 0 "); InvalidateRect(hWnd, NULL, TRUE); break;
		case Difficulty_E:  Bomb_number = 45; game_result = 0; New_game(hWnd); SetWindowText(hWnd_result, L" 0 "); InvalidateRect(hWnd, NULL, TRUE); break;
		case Difficulty_M:  Bomb_number = 60; game_result = 0; New_game(hWnd); SetWindowText(hWnd_result, L" 0 "); InvalidateRect(hWnd, NULL, TRUE); break;
		case Difficulty_H:  Bomb_number = 90; game_result = 0; New_game(hWnd); SetWindowText(hWnd_result, L" 0 "); InvalidateRect(hWnd, NULL, TRUE); break;
		case Difficulty_SH: Bomb_number = 140; game_result = 0; New_game(hWnd); SetWindowText(hWnd_result, L" 0 "); InvalidateRect(hWnd, NULL, TRUE); break;
		case Difficulty_L:  Bomb_number = 200; game_result = 0; New_game(hWnd); SetWindowText(hWnd_result, L" 0 "); InvalidateRect(hWnd, NULL, TRUE); break;
		case About_me: ShellExecute(0, 0, L"https://pixhunter.live/", 0, 0, SW_SHOW); break;

		case Menu_Click_Exit: DestroyWindow(hWnd);break;
		}
		break;
	}
	case WM_CREATE:
	{
		Menu_main(hWnd);
		full_buttons(hWnd, hInst);
		full_table(hDC, hWnd);
		hWnd_result = CreateWindow(L"Edit", L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | ES_CENTER | ES_READONLY, 385, 20, 80, 14, hWnd, (HMENU)(9393), hInst, NULL);
		hWnd_time = CreateWindow(L"Edit", L"0", WS_TABSTOP | WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON | ES_CENTER | ES_READONLY, 110, 20, 80, 14, hWnd, (HMENU)(9393), hInst, NULL);
		
		SetClassLong(hWnd, GCL_HBRBACKGROUND,(LONG)CreateSolidBrush(RGB(200, 160, 255)));
		break;
	}

	case WM_PAINT:
	{
		hDC = BeginPaint(hWnd, &ps);
		SetBkMode(hDC, TRANSPARENT);
	
		paint_pic(hDC, 0, 0, 600, 64);
		paint_tables(hDC, hWnd);
		paint_letters(hDC);
		paint_NULL_up(hDC);
		
		EndPaint(hWnd, &ps);
		break;
	}
	case WM_SIZE:
	{
		width = LOWORD(lParam);
		height = HIWORD(lParam);
		return 0;
	}

	case WM_CLOSE:
	{
		userReply = MessageBox(hWnd, L"A u really wanna close me?",
			L"", MB_YESNO | MB_ICONQUESTION);
		if (IDYES == userReply)
			DestroyWindow(hWnd);
		break;
	}
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default: return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	
	return 0;
}


//====================================================================
void full_table(HDC hDC, HWND hWnd)
{
	Bomb_number_els = Bomb_number;
	while (Bomb_number_els != 0)
	{
		srand((unsigned int)time(NULL));
		

		for (int i = 0; i < size_of_war; i++)
		{
			for (int j = 0; j < size_of_war; j++)
			{
				if (((rand() % 10) == 0) and (Bomb_number_els > 0) and (mine_war[i][j] != 9))
				{
					std::cout << "bomb ---" << i << " - " << j << " " << " - " << Bomb_number_els << std::endl;
					mine_war[i][j] = 9;

					Bomb_number_els--;
				}

				

			}
		}
	}

	for (int i = 0; i < size_of_war; i++)
	{
		for (int j = 0; j < size_of_war; j++)
		{
			int n = 0;
			if (mine_war[i][j] != 9)
			{
				if ((mine_war[i + 1][j] == 9) and (i + 1 < 16) and (j >= 0))n++;
				if ((mine_war[i][j + 1] == 9) and (j + 1 < 16) and (i >= 0))n++;
				if ((mine_war[i - 1][j] == 9) and (i - 1 >= 0) and (j  < 16)) n++;
				if ((mine_war[i][j - 1] == 9) and (j - 1 >= 0) and (i < 16))n++;
				if ((mine_war[i + 1][j + 1] == 9) and (i + 1 < 16) and (j + 1 < 16)) n++;
				if ((mine_war[i - 1][j - 1] == 9) and (j - 1 >= 0) and (i - 1 >= 0))n++;
				if ((mine_war[i - 1][j + 1] == 9) and (i - 1 < 16) and (j + 1>= 0)) n++;
				if ((mine_war[i + 1][j - 1] == 9) and (j - 1 >= 0) and (i + 1 < 16))n++;

				mine_war[i][j] += n;

			}
			else mine_war[i][j] = 9;

			
		}
	}
	return;
}


//====================================================================
void paint_tables(HDC hDC, HWND hWnd)
{
	for (int i = 0; i < size_of_war; i++)
	{
		for (int j = 0; j < size_of_war; j++)
		{
			switch (mine_war[i][j])
			{
			case 0: 
				paint_NULL(hDC, 32 + i * 32, 64 + j * 32, 32 + (i + 1) * 32, 64 + (j + 1) * 32);
				
				break;
			case 1: case 2: case 3: case 4: case 5: case 6: case 7: case 8:
				paint_N1(hDC, 32 + i * 32, 64 + j * 32, 32 + (i + 1) * 32, 64 + (j + 1) * 32, mine_war[i][j]);
				 
				break;
			case 9: paint_Bomb(hDC, 32 + i * 32, 64 + j * 32, 32 + (i + 1) * 32, 64 + (j + 1) * 32); 
				
				break;
			default:
				break;
			}
		}
	}
	return;
}

//====================================================================
void full_buttons(HWND hWnd, HINSTANCE hInst)
{
	for (int i = 0; i < size_of_war; i++)
	{
		for (int j = 0; j < size_of_war; j++)
		{
			buttom_bomb(hWnd, hInst, 32 + i * 32, 64 + j * 32, 32 , 32 , i , j);
			
		}
	}return;
}

//====================================================================
void New_game(HWND hWnd)
{
	game_result = 0;
	game_von_mode = size_of_war * size_of_war;

	for (int i = 0; i < size_of_war; i++)
	{
		for (int j = 0; j < size_of_war; j++)
		{
			mine_war[i][j] = NULL;
			if (hwnd_buttonEndInput[i][j])
				SendMessage(hwnd_buttonEndInput[i][j], WM_CLOSE, 0, 0);
		}
	}
	full_table(hDC, hWnd);
	full_buttons(hWnd, hInst);
	

	std::cout << "update" << std::endl;
	return;

}

//====================================================================
void open_buttoms(int i, int j)
{
	if (((! hwnd_buttonEndInput[i][j]) ))  return;

		SendMessage(hwnd_buttonEndInput[i][j], WM_CLOSE, 0, 0);
		hwnd_buttonEndInput[i][j] = NULL;
		game_von_mode--;
		game_result += mine_war[i][j] * 15;
		TCHAR p[17];
		_itot(game_result, p, 10);
		SetWindowText(hWnd_result, p);
		_itot(game_result/15, p, 10);
		SetWindowText(hWnd_time, p);
	
	if (mine_war[i][j] == 0)
	{

			if ((i >= 0) and (i < 16) and (j - 1 >= 0) ) { open_buttoms(i, j - 1); }
			if ((i + 1 < 16) and (j >= 0) and (j < 16)) { open_buttoms(i + 1, j); }
			if ((j >= 0) and (j < 16) and (i - 1 >= 0)) { open_buttoms(i - 1, j); }
			if ((i >= 0) and (i < 16) and (j + 1 < 16)) { open_buttoms(i, j + 1); }

			if ((j - 1 >= 0) and (i - 1 >= 0)) { open_buttoms(i - 1, j - 1); }
			if ((i + 1 < 16) and (j + 1 < 16)) { open_buttoms(i + 1, j + 1); }
			if ((j - 1 >= 0) and (i + 1 < 16)) { open_buttoms(i + 1, j - 1); }
			if ((j + 1 < 16) and (i - 1 >= 0)) { open_buttoms(i - 1, j + 1); }
		
	}
	return;
}