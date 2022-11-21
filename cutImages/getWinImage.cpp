#include "getWinImage.h"


HBITMAP cutWindow(std::wstring windowname)
{
    RECT rect;
    HWND hwnd = FindWindow(windowname.c_str(), NULL);
    GetWindowRect(hwnd, &rect);
    HDC hScrDC = ::GetDC(hwnd);                            //创建屏幕DC  
    HDC hMemDC = CreateCompatibleDC(hScrDC);                //创建内存DC  
    HBITMAP bitmap = ::CreateCompatibleBitmap(hScrDC, rect.right - rect.left, rect.bottom - rect.top); //创建兼容位图  
    HBITMAP OldBitmap = (HBITMAP)::SelectObject(hMemDC, bitmap);    //把位图选进内存DC  
    PrintWindow(hwnd, hMemDC, PW_CLIENTONLY);
    return bitmap;
}

HBITMAP cutWindow(HWND windowND)
{
    RECT rect;
    GetWindowRect(windowND, &rect);
    HDC hScrDC = ::GetDC(windowND);                            //创建屏幕DC  
    HDC hMemDC = CreateCompatibleDC(hScrDC);                //创建内存DC  
    HBITMAP bitmap = ::CreateCompatibleBitmap(hScrDC, rect.right - rect.left, rect.bottom - rect.top); //创建兼容位图  
    HBITMAP OldBitmap = (HBITMAP)::SelectObject(hMemDC, bitmap);    //把位图选进内存DC  
    PrintWindow(windowND, hMemDC, PW_CLIENTONLY);
    return bitmap;

}

HBITMAP cutFullWindow()
{
    RECT rect;
    HWND winND = GetDesktopWindow();
    GetWindowRect(winND, &rect);
    HDC winDC = GetWindowDC(winND);
    HDC hMemDC = CreateCompatibleDC(winDC);
    HBITMAP bitmap = ::CreateCompatibleBitmap(winDC, rect.right - rect.left, rect.bottom - rect.top);
    SelectObject(hMemDC, bitmap);
    BitBlt(hMemDC, 0, 0, rect.right - rect.left, rect.bottom - rect.top, winDC, 0, 0, SRCCOPY);
    return bitmap;
}

HWND getCursorND()
{
    POINT pNow = { 0,0 };
    if (GetCursorPos(&pNow))  // 获取鼠标当前位置

    {

        HWND hwndPointNow = NULL;

        hwndPointNow = WindowFromPoint(pNow);  // 获取鼠标所在窗口的句柄

        if (hwndPointNow)

        {
            //    //cout << "Success!!" << endl;
            //    Sleep(1000);
            //    char szWindowTitle[50];
            //    ::GetWindowTextA(hwndPointNow, szWindowTitle, sizeof(szWindowTitle));  // 获取窗口标题
            //    std::cout << szWindowTitle << endl;
            //}
            return hwndPointNow;
        }
        else {
            return NULL;
        }
    }
}
