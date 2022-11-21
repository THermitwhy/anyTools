#pragma once
#include<Windows.h>
#include<iostream>

HBITMAP cutWindow(std::wstring windowname);
HBITMAP cutWindow(HWND windowND);
HBITMAP cutFullWindow();

HWND getCursorND();