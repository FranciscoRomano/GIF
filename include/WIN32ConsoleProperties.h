#ifndef WIN32ConsoleProperties_h
#define WIN32ConsoleProperties_h 1
#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#ifndef WINCALL
#define WINCALL __declspec(dllexport)
#endif//WINCALL

#include <Windows.h>
#include "WIN32ConsoleInstance.h"

/// <summary> [win32] console properties handle </summary>
typedef struct WIN32ConsoleProperties {
    COORD                        cursorPos;          // cursor position
    CONSOLE_CURSOR_INFO          cursorInfo;         // cursor information
    CONSOLE_FONT_INFOEX          fontInfoEx;         // font information
    CONSOLE_HISTORY_INFO         historyInfo;        // history information
    CONSOLE_SCREEN_BUFFER_INFOEX screenBufferInfoEx; // screen buffer information
    LONG                         style;              // window style
    DWORD                        modeIn;             // input mode
    DWORD                        modeOut;            // output mode
} WIN32ConsoleProperties;

/// <summary> [win32] get console properties </summary>
/// <param name="instance"> instance pointer </param>
/// <param name="properties"> properties pointer </param>
WINCALL void WINAPI WIN32GetConsoleProperties(WIN32ConsoleInstance* instance, WIN32ConsoleProperties* properties);

/// <summary> [win32] set console properties </summary>
/// <param name="instance"> instance pointer </param>
/// <param name="properties"> properties pointer </param>
WINCALL void WINAPI WIN32SetConsoleProperties(WIN32ConsoleInstance* instance, WIN32ConsoleProperties* properties);

/// <summary> [win32] set console cursor info property </summary>
/// <param name="instance"> instance pointer </param>
/// <param name="properties"> properties pointer </param>
WINCALL void WINAPI WIN32SetConsolePropertyCursorInfo(WIN32ConsoleInstance* instance, WIN32ConsoleProperties* properties);

/// <summary> [win32] set console cursor position property </summary>
/// <param name="instance"> instance pointer </param>
/// <param name="properties"> properties pointer </param>
WINCALL void WINAPI WIN32SetConsolePropertyCursorPosition(WIN32ConsoleInstance* instance, WIN32ConsoleProperties* properties);

/// <summary> [win32] set console font info property </summary>
/// <param name="instance"> instance pointer </param>
/// <param name="properties"> properties pointer </param>
WINCALL void WINAPI WIN32SetConsolePropertyFontInfo(WIN32ConsoleInstance* instance, WIN32ConsoleProperties* properties);

/// <summary> [win32] set console history info property </summary>
/// <param name="instance"> instance pointer </param>
/// <param name="properties"> properties pointer </param>
WINCALL void WINAPI WIN32SetConsolePropertyHistoryInfo(WIN32ConsoleInstance* instance, WIN32ConsoleProperties* properties);

/// <summary> [win32] set console input mode property </summary>
/// <param name="instance"> instance pointer </param>
/// <param name="properties"> properties pointer </param>
WINCALL void WINAPI WIN32SetConsolePropertyInputMode(WIN32ConsoleInstance* instance, WIN32ConsoleProperties* properties);

/// <summary> [win32] set console output mode property </summary>
/// <param name="instance"> instance pointer </param>
/// <param name="properties"> properties pointer </param>
WINCALL void WINAPI WIN32SetConsolePropertyOutputMode(WIN32ConsoleInstance* instance, WIN32ConsoleProperties* properties);

/// <summary> [win32] set console screen buffer info property </summary>
/// <param name="instance"> instance pointer </param>
/// <param name="properties"> properties pointer </param>
WINCALL void WINAPI WIN32SetConsolePropertyScreenBufferInfo(WIN32ConsoleInstance* instance, WIN32ConsoleProperties* properties);

/// <summary> [win32] set console window style property </summary>
/// <param name="instance"> instance pointer </param>
/// <param name="properties"> properties pointer </param>
WINCALL void WINAPI WIN32SetConsolePropertyWindowStyle(WIN32ConsoleInstance* instance, WIN32ConsoleProperties* properties);

#ifdef __cplusplus
}
#endif//__cplusplus
#endif//WIN32ConsoleProperties_h