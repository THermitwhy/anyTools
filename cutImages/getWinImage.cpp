#include "getWinImage.h"


HBITMAP cutWindow(std::wstring windowname)
{
    RECT rect;
    HWND hwnd = FindWindow(windowname.c_str(), NULL);
    GetWindowRect(hwnd, &rect);
    HDC hScrDC = ::GetDC(hwnd);                            //������ĻDC  
    HDC hMemDC = CreateCompatibleDC(hScrDC);                //�����ڴ�DC  
    HBITMAP bitmap = ::CreateCompatibleBitmap(hScrDC, rect.right - rect.left, rect.bottom - rect.top); //��������λͼ  
    HBITMAP OldBitmap = (HBITMAP)::SelectObject(hMemDC, bitmap);    //��λͼѡ���ڴ�DC  
    PrintWindow(hwnd, hMemDC, PW_CLIENTONLY);
    return bitmap;
}

HBITMAP cutWindow(HWND windowND)
{
    RECT rect;
    GetWindowRect(windowND, &rect);
    HDC hScrDC = ::GetDC(windowND);                            //������ĻDC  
    HDC hMemDC = CreateCompatibleDC(hScrDC);                //�����ڴ�DC  
    HBITMAP bitmap = ::CreateCompatibleBitmap(hScrDC, rect.right - rect.left, rect.bottom - rect.top); //��������λͼ  
    HBITMAP OldBitmap = (HBITMAP)::SelectObject(hMemDC, bitmap);    //��λͼѡ���ڴ�DC  
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
    if (GetCursorPos(&pNow))  // ��ȡ��굱ǰλ��

    {

        HWND hwndPointNow = NULL;

        hwndPointNow = WindowFromPoint(pNow);  // ��ȡ������ڴ��ڵľ��

        if (hwndPointNow)

        {
            //    //cout << "Success!!" << endl;
            //    Sleep(1000);
            //    char szWindowTitle[50];
            //    ::GetWindowTextA(hwndPointNow, szWindowTitle, sizeof(szWindowTitle));  // ��ȡ���ڱ���
            //    std::cout << szWindowTitle << endl;
            //}
            return hwndPointNow;
        }
        else {
            return NULL;
        }
    }
}
