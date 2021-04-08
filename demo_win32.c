/*
 * @Author: your name
 * @Date: 2021-04-08 18:56:55
 * @LastEditTime: 2021-04-08 19:08:46
 * @LastEditors: your name
 * @Description: In User Settings Edit
 * @FilePath: \study_win32API\demo_win32.c
 */
#include <windows.h>
#include <stdio.h>

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, 
            HINSTANCE hPrevInstance,
            PSTR szCmdLine, 
            int iCmdShow)
{
    static TCHAR szAppName[] = TEXT("Mywindows");
    HWND hwnd;
    MSG msg;
    WNDCLASS wndclass;
    //测试用
    int a = 0;

    wndclass.style = CS_HREDRAW;
    wndclass.lpfnWndProc = WndProc;
    wndclass.cbClsExtra = 0;
    wndclass.cbWndExtra = 0;
    wndclass.hInstance = hInstance;
    wndclass.hIcon = LoadCursor(NULL, IDI_APPLICATION);
    wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
    wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    wndclass.lpszMenuName = NULL;
    wndclass.lpszClassName = szAppName;

    
    if(!RegisterClass(&wndclass))
    {
        MessageBox(NULL, TEXT("错误"), szAppName, MB_ICONERROR);
        return 0;
    }
    hwnd = CreateWindow(szAppName,
        TEXT("111"),
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL );
    

    ShowWindow(hwnd, iCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    RECT rect;

    switch(message)
    {
        case WM_PAINT:
            hdc = BeginPaint(hwnd, &ps);
            GetClientRect(hwnd, &rect);
            DrawText(hdc, TEXT("hhhhhhhhhhhh"), -1, &rect,
                DT_SINGLELINE | DT_CENTER | DT_VCENTER);
            EndPaint(hwnd, &ps);
            return 0;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            OutputDebugStr("WM_CLOSE消息\n");
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_RBUTTONDBLCLK:
            MessageBox(hwnd, TEXT("right click"), TEXT("message"), MB_OK);
            return 0;
        case WM_LBUTTONDOWN:
            MessageBox(hwnd, TEXT("left click"), TEXT("message"), MB_OK);
            return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}