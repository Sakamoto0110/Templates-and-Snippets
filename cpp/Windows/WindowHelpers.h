#pragma once

#include <cstdio>


#include <Windows.h>
WNDCLASSW GetDefaultWNDCLASS();


typedef class WC_FACTORY_t
{
public:
    static bool AllowOverrite;


    static WC_FACTORY_t& WindowStyle(UINT data, WC_FACTORY_t* _pwc = _LPWNDREG);
    static WC_FACTORY_t& ClassStyle(UINT data, WC_FACTORY_t* _pwc = _LPWNDREG);
    static WC_FACTORY_t& ClassName(const wchar_t* data, WC_FACTORY_t* _pwc = _LPWNDREG);
    static WC_FACTORY_t& HInstance(HINSTANCE data, WC_FACTORY_t* _pwc = _LPWNDREG);
    static WC_FACTORY_t& WinProc(WNDPROC func, WC_FACTORY_t* _pwc = _LPWNDREG);
    static WC_FACTORY_t& Other(WC_FACTORY_t* _pwc = _LPWNDREG);

    static WC_FACTORY_t& WNDCLASS(WNDCLASSW, WC_FACTORY_t* _pwc = _LPWNDREG);

    friend WC_FACTORY_t& CreateWNDREG(bool overwrite);


    operator WNDCLASSW* () {
        return  &_WC;
    }

    ~WC_FACTORY_t();

protected:
    WC_FACTORY_t(bool overwrite);
    static WC_FACTORY_t* GetLPWNDREG();
private:
    static WC_FACTORY_t* _LPWNDREG;
    WNDCLASSW _WC;

};


bool WC_FACTORY_t::AllowOverrite = true;






//
// Exemple of WindowProc for the window class
//
LRESULT CALLBACK WindowProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        printf("Window created\n");
        break;
    case WM_DESTROY:

        PostQuitMessage(0);
        break;
    case WM_PAINT:

        break;
    }

    return DefWindowProcW(hWnd, message, wParam, lParam);

}
WNDCLASSW GetDefaultWNDCLASS()
{
    return{
        CS_HREDRAW | CS_VREDRAW,
        WindowProc,
        0,
        0,
        0, // hinst
        LoadIcon(NULL, IDI_APPLICATION),
        LoadCursor(NULL, IDC_ARROW),
        GetSysColorBrush(COLOR_3DFACE),
        NULL,
        L"Default"
    };
}


// WINREG
//=================================================
// Variables

WC_FACTORY_t* WC_FACTORY_t::_LPWNDREG = NULL;

//=================================================
// Ctor


WC_FACTORY_t::WC_FACTORY_t(bool overwrite) : _WC(GetDefaultWNDCLASS())
{
    if (_LPWNDREG != NULL && overwrite)
    {
        printf("Overwriting\n");
        _LPWNDREG->~WC_FACTORY_t();
        _LPWNDREG = this;
    }
    if (_LPWNDREG != NULL && !overwrite)
        printf("Overwrite not enabled.\n");
}

WC_FACTORY_t::~WC_FACTORY_t()
{
    if (_LPWNDREG != NULL)
        _LPWNDREG = NULL;
}

//=================================================
// Member methods


WC_FACTORY_t& WC_FACTORY_t::ClassStyle(UINT data, WC_FACTORY_t* _pwc)
{
    (*_pwc)._WC.style = data;
    return *_pwc;
}

WC_FACTORY_t& WC_FACTORY_t::WindowStyle(UINT data, WC_FACTORY_t* _pwc)
{
    (*_pwc)._WC.style = data;
    return *_pwc;
}

WC_FACTORY_t& WC_FACTORY_t::ClassName(const wchar_t* data, WC_FACTORY_t* _pwc)
{
    (*_pwc)._WC.lpszClassName = data;
    return *_pwc;
}

WC_FACTORY_t& WC_FACTORY_t::HInstance(HINSTANCE data, WC_FACTORY_t* _pwc)
{
    (*_pwc)._WC.hInstance = data;
    return *_pwc;
}

WC_FACTORY_t& WC_FACTORY_t::WinProc(WNDPROC func, WC_FACTORY_t* _pwc)
{
    (*_pwc)._WC.lpfnWndProc = func;
    return *_pwc;
}

WC_FACTORY_t& WC_FACTORY_t::Other(WC_FACTORY_t* _pwc)
{
    (*_pwc)._WC.cbClsExtra = 0;
    (*_pwc)._WC.cbWndExtra = 0;
    (*_pwc)._WC.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
    (*_pwc)._WC.lpszMenuName = NULL;
    (*_pwc)._WC.hCursor = LoadCursor(NULL, IDC_ARROW);
    (*_pwc)._WC.hIcon = LoadIcon(NULL, IDI_APPLICATION);


    return *_pwc;
}



WC_FACTORY_t& WC_FACTORY_t::WNDCLASS(WNDCLASSW wc, WC_FACTORY_t* _pwc)
{
    (*_pwc)._WC.hInstance = wc.hInstance;
    (*_pwc)._WC.lpfnWndProc = wc.lpfnWndProc;
    (*_pwc)._WC.lpszClassName = wc.lpszClassName;
    (*_pwc)._WC.style = wc.style;
    (*_pwc)._WC.cbClsExtra = wc.cbClsExtra;
    (*_pwc)._WC.cbWndExtra = wc.cbWndExtra;
    (*_pwc)._WC.hbrBackground = wc.hbrBackground;
    (*_pwc)._WC.lpszMenuName = wc.lpszMenuName;
    (*_pwc)._WC.hCursor = wc.hCursor;
    (*_pwc)._WC.hIcon = wc.hIcon;
    return *_pwc;
}


WC_FACTORY_t* WC_FACTORY_t::GetLPWNDREG()
{
    return _LPWNDREG;
}

//=================================================
// Friends



WC_FACTORY_t& CreateWNDREG(bool overwrite)
{
    if (WC_FACTORY_t::_LPWNDREG == NULL)
    {
        printf("Creating.\n");
        WC_FACTORY_t::_LPWNDREG = new WC_FACTORY_t(overwrite);
    }
    else if (WC_FACTORY_t::_LPWNDREG != NULL && overwrite)
    {
        printf("Overwriting.\n");
        WC_FACTORY_t::_LPWNDREG->~WC_FACTORY_t();
        WC_FACTORY_t::_LPWNDREG = NULL;
        WC_FACTORY_t::_LPWNDREG = new WC_FACTORY_t(overwrite);
    }
    else if (WC_FACTORY_t::_LPWNDREG != NULL && !overwrite)
    {
        printf("Overwrite not enabled.\n");
    }

    return *WC_FACTORY_t::_LPWNDREG;
}














