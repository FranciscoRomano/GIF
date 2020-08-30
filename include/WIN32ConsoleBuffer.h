#ifndef WIN32ConsoleBuffer_h
#define WIN32ConsoleBuffer_h 1
#ifdef __cplusplus
extern "C" {
#endif//__cplusplus

#ifndef WINCALL
#define WINCALL __declspec(dllimport)
#endif//WINCALL

#include <Windows.h>
#include "WIN32ConsoleInstance.h"

/// <summary> [win32] console buffer handle </summary>
typedef struct WIN32ConsoleBuffer {
    CHAR_INFO* pCharInfo;   // buffer data
    COORD      writeSize;   // buffer 2D size
    UINT       writeLength; // buffer array length
} WIN32ConsoleBuffer;

/// <summary> [win32] allocate console buffer memory </summary>
/// <param name="size"> buffer size </param>
/// <param name="buffer"> buffer pointer </param>
WINCALL void WINAPI WIN32AllocConsoleBuffer(const COORD size, WIN32ConsoleBuffer* buffer);

/// <summary> [win32] free console buffer memory </summary>
/// <param name="buffer"> buffer pointer </param>
WINCALL void WINAPI WIN32FreeConsoleBuffer(WIN32ConsoleBuffer* buffer);

/// <summary> [win32] set console buffer attributes (color) </summary>
/// <param name="buffer"> buffer pointer </param>
/// <param name="index"> data index </param>
/// <param name="value"> data value </param>
WINCALL void WINAPI WIN32SetConsoleBufferAttributes(WIN32ConsoleBuffer* buffer, const UINT index, const WORD value);

/// <summary> [win32] set console buffer background (color) </summary>
/// <param name="buffer"> buffer pointer </param>
/// <param name="index"> data index </param>
/// <param name="value"> data value </param>
WINCALL void WINAPI WIN32SetConsoleBufferBackground(WIN32ConsoleBuffer* buffer, const UINT index, const CHAR value);

/// <summary> [win32] set console buffer character (ascii) </summary>
/// <param name="buffer"> buffer pointer </param>
/// <param name="index"> data index </param>
/// <param name="value"> data value </param>
WINCALL void WINAPI WIN32SetConsoleBufferCharacterA(WIN32ConsoleBuffer* buffer, const UINT index, const CHAR value);

/// <summary> [win32] set console buffer character (unicode) </summary>
/// <param name="buffer"> buffer pointer </param>
/// <param name="index"> data index </param>
/// <param name="value"> data value </param>
WINCALL void WINAPI WIN32SetConsoleBufferCharacterW(WIN32ConsoleBuffer* buffer, const UINT index, const WCHAR value);

/// <summary> [win32] set console buffer foreground (color) </summary>
/// <param name="buffer"> buffer pointer </param>
/// <param name="index"> data index </param>
/// <param name="value"> data value </param>
WINCALL void WINAPI WIN32SetConsoleBufferForeground(WIN32ConsoleBuffer* buffer, const UINT index, const CHAR value);

/// <summary> [win32] write console buffer (ascii) </summary>
/// <param name="instance"> instance pointer </param>
/// <param name="buffer"> buffer pointer </param>
/// <param name="coord"> write coord </param>
/// <param name="region"> write region </param>
WINCALL void WINAPI WIN32WriteConsoleBufferA(WIN32ConsoleInstance* instance, WIN32ConsoleBuffer* buffer, const COORD coord, const PSMALL_RECT region);

/// <summary> [win32] write console buffer (unicode) </summary>
/// <param name="instance"> instance pointer </param>
/// <param name="buffer"> buffer pointer </param>
/// <param name="coord"> write coord </param>
/// <param name="region"> write region </param>
WINCALL void WINAPI WIN32WriteConsoleBufferW(WIN32ConsoleInstance* instance, WIN32ConsoleBuffer* buffer, const COORD coord, const PSMALL_RECT region);

#ifdef __cplusplus
}
#endif//__cplusplus
#endif//WIN32ConsoleBuffer_h