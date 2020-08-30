#ifndef WIN32ConsoleInstance_h
#define WIN32ConsoleInstance_h 1
#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#ifndef WINCALL
#define WINCALL __declspec(dllexport)
#endif//WINCALL

#include <Windows.h>

/// <summary> [win32] console input record event callback </summary>
typedef void (*PFN_WIN32ConsoleInputCallback)(INPUT_RECORD);

/// <summary> [win32] console instance handle </summary>
typedef struct WIN32ConsoleInstance {
    HANDLE                   hIn;              // input handle
    HANDLE                   hOut;             // output handle
    HWND                     hWnd;             // window handle
    HINSTANCE                hInstance;        // instance handle
    CHAR                     path[MAX_PATH];   // executable path
} WIN32ConsoleInstance;

/// <summary> [win32] allocate new console instance </summary>
WINCALL void WINAPI WIN32AllocConsoleInstance();

/// <summary> [win32] free current console instance </summary>
WINCALL void WINAPI WIN32FreeConsoleInstance();

/// <summary> [win32] get console instance </summary>
/// <param name="instance"> instance pointer </param>
WINCALL void WINAPI WIN32GetConsoleInstance(WIN32ConsoleInstance* instance);

/// <summary> [win32] flush console instance input events </summary>
/// <param name="instance"> instance pointer </param>
WINCALL void WINAPI WIN32FlushConsoleInstanceInput(WIN32ConsoleInstance* instance);

/// <summary> [win32] read console instance input events (ascii) </summary>
/// <param name="instance"> instance pointer </param>
/// <param name="callback"> input event callback </param>
WINCALL void WINAPI WIN32ReadConsoleInstanceInputA(WIN32ConsoleInstance* instance, PFN_WIN32ConsoleInputCallback callback);

/// <summary> [win32] read console instance input events (unicode) </summary>
/// <param name="instance"> instance pointer </param>
/// <param name="callback"> input event callback </param>
WINCALL void WINAPI WIN32ReadConsoleInstanceInputW(WIN32ConsoleInstance* instance, PFN_WIN32ConsoleInputCallback callback);

#ifdef __cplusplus
}
#endif//__cplusplus
#endif//WIN32ConsoleInstance_h