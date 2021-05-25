#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS
#include <windows.h>
#include <iostream>
#include <Shlwapi.h>
#include <tchar.h>
#include <cmath>
#include "resource.h"
#include "resource1.h"
#include <process.h>



LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
#define WMAIN_CLASSNAME     "Calculator"
#define WMAIN_CAPTION       "Калькулятор"

TCHAR buf[256];

HINSTANCE hInstance;



int main(int nCmdShow) {
    /*HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);*/
    HWND hWnd;
    MSG msg;
    WNDCLASS wc;

    

    HICON hIcon1 = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(MAIN_ICON));
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = hIcon1;

    /*wc.hInstance = hInstance;*/
    wc.lpfnWndProc = WndProc;
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpszClassName = WMAIN_CLASSNAME;
    wc.lpszMenuName = NULL;

    if (!RegisterClass(&wc))
        return 1;

    hWnd = CreateWindow(WMAIN_CLASSNAME, WMAIN_CAPTION, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_VISIBLE, CW_USEDEFAULT, CW_USEDEFAULT, 320, 419, HWND_DESKTOP, NULL, hInstance, 0);

    ShowWindow(hWnd, nCmdShow);
    UpdateWindow(hWnd);

    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}





LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    static HWND button[34], hEdit;
   
    switch (message)
    {   
    case WM_CREATE:
        
        hEdit = CreateWindow(("edit"), (""), WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 6, 10, 293, 65, hWnd, (HMENU)ID_EDIT, hInstance, 0);
        button[0] = CreateWindow("button", "+", WS_VISIBLE | WS_CHILD, 185, 330, 55, 45, hWnd, (HMENU)ID_BUTTON_PLUS, hInstance, 0);
        button[1] = CreateWindow("button", "-", WS_VISIBLE | WS_CHILD, 185, 280, 55, 45, hWnd, (HMENU)ID_BUTTON_MINUS, hInstance, 0);
        button[2] = CreateWindow("button", "*", WS_VISIBLE | WS_CHILD, 185, 230, 55, 45, hWnd, (HMENU)ID_BUTTON_MULTIPLY, hInstance, 0);
        button[3] = CreateWindow("button", "/", WS_VISIBLE | WS_CHILD, 185, 180, 55, 45, hWnd, (HMENU)ID_BUTTON_DIVIDE, hInstance, 0);
        button[4] = CreateWindow("button", "AC", WS_VISIBLE | WS_CHILD, 245, 130, 55, 45, hWnd, (HMENU)ID_BUTTON_AC, hInstance, 0);
        button[5] = CreateWindow("button", "sqrt", WS_VISIBLE | WS_CHILD, 125, 130, 55, 45, hWnd, (HMENU)ID_BUTTON_SQRT, hInstance, 0);
        button[8] = CreateWindow("button", ".", WS_VISIBLE | WS_CHILD, 65, 330, 55, 45, hWnd, (HMENU)ID_BUTTON_DOT, hInstance, 0);
        button[9] = CreateWindow("button", "=", WS_VISIBLE | WS_CHILD, 125, 330, 55, 45, hWnd, (HMENU)ID_BUTTON_COMPUTE, hInstance, 0);
        button[10] = CreateWindow("button", "0", WS_VISIBLE | WS_CHILD, 5, 330, 55, 45, hWnd, (HMENU)ID_BUTTON_0, hInstance, 0);
        button[11] = CreateWindow("button", "1", WS_VISIBLE | WS_CHILD, 5, 280, 55, 45, hWnd, (HMENU)ID_BUTTON_1, hInstance, 0);
        button[12] = CreateWindow("button", "2", WS_VISIBLE | WS_CHILD, 65, 280, 55, 45, hWnd, (HMENU)ID_BUTTON_2, hInstance, 0);
        button[13] = CreateWindow("button", "3", WS_VISIBLE | WS_CHILD, 125, 280, 55, 45, hWnd, (HMENU)ID_BUTTON_3, hInstance, 0);
        button[14] = CreateWindow("button", "4", WS_VISIBLE | WS_CHILD, 5, 230, 55, 45, hWnd, (HMENU)ID_BUTTON_4, hInstance, 0);
        button[15] = CreateWindow("button", "5", WS_VISIBLE | WS_CHILD, 65, 230, 55, 45, hWnd, (HMENU)ID_BUTTON_5, hInstance, 0);
        button[16] = CreateWindow("button", "6", WS_VISIBLE | WS_CHILD, 125, 230, 55, 45, hWnd, (HMENU)ID_BUTTON_6, hInstance, 0);
        button[17] = CreateWindow("button", "7", WS_VISIBLE | WS_CHILD, 5, 180, 55, 45, hWnd, (HMENU)ID_BUTTON_7, hInstance, 0);
        button[18] = CreateWindow("button", "8", WS_VISIBLE | WS_CHILD, 65, 180, 55, 45, hWnd, (HMENU)ID_BUTTON_8, hInstance, 0);
        button[19] = CreateWindow("button", "9", WS_VISIBLE | WS_CHILD, 125, 180, 55, 45, hWnd, (HMENU)ID_BUTTON_9, hInstance, 0);
        button[20] = CreateWindow("button", "DEG", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 245,  85, 55, 20, hWnd, (HMENU)ID_BUTTON_DEG, hInstance, 0);
        button[21] = CreateWindow("button", "RAD", WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON, 245, 105, 55, 20, hWnd, (HMENU)ID_BUTTON_RAD, hInstance, 0);
        SendMessage(button[21], BM_SETCHECK, BST_CHECKED, 0);
        button[22] = CreateWindow("button", "^", WS_VISIBLE | WS_CHILD,  185, 130, 55, 45, hWnd, (HMENU)ID_BUTTON_POW, hInstance, 0);
        button[23] = CreateWindow("button", "sin", WS_VISIBLE | WS_CHILD, 245, 180, 55, 45, hWnd, (HMENU)ID_BUTTON_SIN, hInstance, 0);
        button[24] = CreateWindow("button", "cos", WS_VISIBLE | WS_CHILD, 245, 230, 55, 45, hWnd, (HMENU)ID_BUTTON_COS, hInstance, 0);
        button[25] = CreateWindow("button", "tg", WS_VISIBLE | WS_CHILD, 245, 280, 55, 45, hWnd, (HMENU)ID_BUTTON_TG, hInstance, 0);
        button[26] = CreateWindow("button", "ctg", WS_VISIBLE | WS_CHILD, 245, 330, 55, 45, hWnd, (HMENU)ID_BUTTON_CTG, hInstance, 0);
        button[27] = CreateWindow("button", "PI",   WS_VISIBLE | WS_CHILD, 5,   85, 40, 40, hWnd, (HMENU)ID_BUTTON_PI, hInstance, 0);
        button[28] = CreateWindow("button", "PI/2", WS_VISIBLE | WS_CHILD, 52,  85, 40, 40, hWnd, (HMENU)ID_BUTTON_PI_2, hInstance, 0);
        button[29] = CreateWindow("button", "PI/3", WS_VISIBLE | WS_CHILD, 99, 85, 40,  40, hWnd, (HMENU)ID_BUTTON_PI_3, hInstance, 0);
        button[30] = CreateWindow("button", "PI/4", WS_VISIBLE | WS_CHILD, 146, 85, 40, 40, hWnd, (HMENU)ID_BUTTON_PI_4, hInstance, 0);
        button[31] = CreateWindow("button", "PI/6", WS_VISIBLE | WS_CHILD, 193, 85, 40, 40, hWnd, (HMENU)ID_BUTTON_PI_6, hInstance, 0);
        button[32] = CreateWindow("button", "(", WS_VISIBLE | WS_CHILD,    5, 130,  55, 45, hWnd, (HMENU)ID_BUTTON_S1, hInstance, 0);
        button[33] = CreateWindow("button", ")", WS_VISIBLE | WS_CHILD,    65, 130,  55, 45, hWnd, (HMENU)ID_BUTTON_S2, hInstance, 0);
        break;
        
    case WM_COMMAND:
        
       
        if ((LOWORD(wParam) == ID_BUTTON_0) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("0"));
            SetWindowText(hEdit, buf);

        }

        if ((LOWORD(wParam) == ID_BUTTON_1) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("1"));
            SetWindowText(hEdit, buf);
           
        }

        if ((LOWORD(wParam) == ID_BUTTON_2) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));

            StrCat(buf, TEXT("2"));
            SetWindowText(hEdit, buf);

        }

        if ((LOWORD(wParam) == ID_BUTTON_3) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            
            StrCat(buf, TEXT("3"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_4) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            
            StrCat(buf, TEXT("4"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_5) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            
            StrCat(buf, TEXT("5"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_6) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            
            StrCat(buf, TEXT("6"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_7) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            
            StrCat(buf, TEXT("7"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_8) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            
            StrCat(buf, TEXT("8"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_9) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            
            StrCat(buf, TEXT("9"));
            SetWindowText(hEdit, buf);
        }
        if (LOWORD(wParam) == ID_BUTTON_DEG)
        {
            isDeg = true;
            isRad = false;
            
        }
        if (LOWORD(wParam) == ID_BUTTON_RAD)
        {
            isDeg = false;
            isRad = true;
            
        }

        if ((LOWORD(wParam) == ID_BUTTON_PLUS) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("+"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_MINUS) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("-"));
            SetWindowText(hEdit, buf);

          
        }

        if ((LOWORD(wParam) == ID_BUTTON_MULTIPLY) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("*"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_DIVIDE) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("/"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_COMPUTE) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            SetWindowText(hEdit, Calculate(buf));

        }

        if ((LOWORD(wParam) == ID_BUTTON_SIN) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("S"));
            SetWindowText(hEdit, buf);

        }

        if ((LOWORD(wParam) == ID_BUTTON_COS) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("C"));
            SetWindowText(hEdit, buf);

        }
        if ((LOWORD(wParam) == ID_BUTTON_TG) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("T"));
            SetWindowText(hEdit, buf);

        }

        if ((LOWORD(wParam) == ID_BUTTON_CTG) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("c"));
            SetWindowText(hEdit, buf);

        }

        if ((LOWORD(wParam) == ID_BUTTON_DOT) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("."));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_AC) && (HIWORD(wParam) == BN_CLICKED))
        {
            SetWindowText(hEdit, TEXT(""));
            buf[0] = 0;
        }

        if ((LOWORD(wParam) == ID_BUTTON_SQRT) && (HIWORD(wParam) == BN_CLICKED))
        {    
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("s"));
            SetWindowText(hEdit, buf);
        }
    
        if ((LOWORD(wParam) == ID_BUTTON_POW) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("^"));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_S1) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("("));
            SetWindowText(hEdit, buf);

        }
        if ((LOWORD(wParam) == ID_BUTTON_S2) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT(")"));
            SetWindowText(hEdit, buf);

        }
        if ((LOWORD(wParam) == ID_BUTTON_PI) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            
            StrCat(buf, TEXT("3.14159265"));
            SetWindowText(hEdit, buf);
           
        }

        if ((LOWORD(wParam) == ID_BUTTON_PI_2) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            
            StrCat(buf, TEXT("1.57079632"));
            SetWindowText(hEdit, buf);
        }
        if ((LOWORD(wParam) == ID_BUTTON_PI_3) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            
            StrCat(buf, TEXT("1.04719755"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_PI_4) && (HIWORD(wParam) == BN_CLICKED))
        {
            GetWindowText(hEdit, buf, sizeof(buf));
            
            StrCat(buf, TEXT("0.78539816"));
            SetWindowText(hEdit, buf);
        }

        if ((LOWORD(wParam) == ID_BUTTON_PI_6) && (HIWORD(wParam) == BN_CLICKED))
        {

            GetWindowText(hEdit, buf, sizeof(buf));
            StrCat(buf, TEXT("0.52359877"));
            SetWindowText(hEdit, buf);
        }

        break;
    
    case WM_DESTROY:
        
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
        break;
    }
    return 0;
}


