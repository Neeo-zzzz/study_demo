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
            //DrawTextW()
            EndPaint(hwnd, &ps);
            return 0;
        case WM_CREATE:
        {
            //在WM_CREATE消息中创建子窗口、控件
            LPCREATESTRUCT psc = (LPCREATESTRUCT)lParam;
            HWND hBtn1;
            //普通按钮BS_PUSHBUTTON
            hBtn1 = CreateWindow(TEXT("BUTTON"), //类名
                TEXT("hello"), //标题名称
                WS_CHILD/*创建子窗口*/|WS_VISIBLE/*可见*/|BS_PUSHBUTTON, //按钮样式,第三个为按钮风格
                300,300, //位置
                100,60, //宽度，高度
                hwnd, //父窗口句柄
                (HMENU)1, //菜单句柄 控件id号 唯一
                ((LPCREATESTRUCT)lParam)->hInstance, //实例句柄
                NULL);
            
            //单选按钮

            HWND hBtn2 = CreateWindow(TEXT("BUTTON"), //类名
                TEXT("hi"), //标题名称
                WS_CHILD/*创建子窗口*/|WS_VISIBLE/*可见*/|BS_AUTORADIOBUTTON, //按钮样式,第三个为按钮风格
                200,300, //位置
                100,60, //宽度，高度
                hwnd, //父窗口句柄
                (HMENU)2, //菜单句柄 控件id号 唯一
                ((LPCREATESTRUCT)lParam)->hInstance, //实例句柄
                NULL);

            //复选按钮
            HWND hBtn3 = CreateWindow(TEXT("BUTTON"), //类名
                TEXT("hi"), //标题名称
                WS_CHILD/*创建子窗口*/|WS_VISIBLE/*可见*/|BS_AUTOCHECKBOX, //按钮样式,第三个为按钮风格
                400,300, //位置
                100,60, //宽度，高度
                hwnd, //父窗口句柄
                (HMENU)3, //菜单句柄 控件id号 唯一
                ((LPCREATESTRUCT)lParam)->hInstance, //实例句柄
                NULL);
            break;
        }
        case WM_CLOSE:
            DestroyWindow(hwnd);
            OutputDebugStr("WM_CLOSE消息\n");
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        case WM_COMMAND:
        {
            //子窗口向父窗口传递消息时使用
            switch(LOWORD(wParam)) //wParam低字节代表空间id
            {
                case 1:
                {
                    //wParam高字节代表控件消息类型
                    if(HIWORD(wParam)==BN_CLICKED) //按下按钮的消息
                    {
                        MessageBox(NULL,TEXT("button"),TEXT("oops"),MB_OK);
                    }
                    break;
                }
                case 2:
                {
                    if(HIWORD(wParam)==BN_CLICKED)
                    {
                        //单击后的处理
                    }
                    //查看按钮状态
                    if(SendMessage((HWND)lParam,BM_GETCHECK,0,0)==BST_CHECKED)
                    {
                        MessageBox(hwnd,TEXT("checked!"),TEXT("tips"),MB_OK);
                    }
                }
                default:
                break;
            }
            break;
        }
        case WM_RBUTTONDBLCLK:
            MessageBox(hwnd, TEXT("right click"), TEXT("message"), MB_OK);
            return 0;
        case WM_LBUTTONDOWN:
            MessageBox(hwnd, TEXT("left click"), TEXT("message"), MB_OK);
            return 0;
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}