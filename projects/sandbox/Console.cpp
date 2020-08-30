#include <cmath>
#include "Console.h"

Console::~Console()
{
	// free console buffer
	WIN32FreeConsoleBuffer(&buffer);
	// reset properties
	WIN32SetConsoleProperties(&instance, &properties[0]);
	// free instance
	WIN32FreeConsoleInstance();
};

Console::Console(const UINT& width, const UINT& height)
{
	// create instance
	WIN32AllocConsoleInstance();
	WIN32GetConsoleInstance(&instance);
	// custom properties
	WIN32GetConsoleProperties(&instance, &properties[0]);
	properties[1] = properties[0];
	properties[1].style = WS_CAPTION | WS_SYSMENU | WS_VISIBLE;
	properties[1].modeIn = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS;
	properties[1].modeOut = 0;
	properties[1].cursorPos.X = 0;
	properties[1].cursorPos.Y = 0;
	properties[1].cursorInfo.bVisible = FALSE;
	properties[1].fontInfoEx.nFont = 0;
	properties[1].fontInfoEx.FontWeight = FW_NORMAL;
	properties[1].fontInfoEx.FontFamily = FF_DONTCARE;
	properties[1].fontInfoEx.dwFontSize.X = 8;
	properties[1].fontInfoEx.dwFontSize.Y = 8;
	wcscpy_s(properties[1].fontInfoEx.FaceName, 12, L"Terminal");
	properties[1].screenBufferInfoEx.dwSize.X = (SHORT)width;
	properties[1].screenBufferInfoEx.dwSize.Y = (SHORT)height;
	properties[1].screenBufferInfoEx.srWindow.Top = 0;
	properties[1].screenBufferInfoEx.srWindow.Left = 0;
	properties[1].screenBufferInfoEx.srWindow.Right = (SHORT)width;
	properties[1].screenBufferInfoEx.srWindow.Bottom = (SHORT)height;
	properties[1].screenBufferInfoEx.dwCursorPosition.X = 0;
	properties[1].screenBufferInfoEx.dwCursorPosition.Y = 0;
	properties[1].screenBufferInfoEx.dwMaximumWindowSize.X = (SHORT)width;
	properties[1].screenBufferInfoEx.dwMaximumWindowSize.Y = (SHORT)height;
	WIN32SetConsoleProperties(&instance, &properties[1]);
	// create console buffer
	WIN32AllocConsoleBuffer(properties[1].screenBufferInfoEx.dwSize, &buffer);
	for (UINT i = 0; i < buffer.writeLength; i++)
	{
		WIN32SetConsoleBufferAttributes(&buffer, i, ((WORD)0));
		WIN32SetConsoleBufferCharacterW(&buffer, i, ((WCHAR)0));
	}
};

void Console::flush()
{
	// flush console input
	WIN32FlushConsoleInstanceInput(&instance);
};

void Console::pixel(const UINT& index, const FLOAT& r, const FLOAT& g, const FLOAT& b)
{
	const static CHAR ascii[] = { (CHAR)0x00, (CHAR)0xb0, (CHAR)0xb1, (CHAR)0xb2, (CHAR)0xDB };
    const static FLOAT length = float(sizeof(ascii)) + 0.015f;
    static FLOAT luminance;
    static UINT character;
    static WORD color;

    // calculate luminance (HSP Color Model)
    luminance = sqrtf(0.299f * powf(r, 2) + 0.587f * powf(g, 2) + 0.114f * powf(b, 2));
    if (luminance > 0.666f) color |= 0x88; else if (luminance > 0.333f) color |= 0x8;

    // calculate color
    color = 0;
    if (r > 0.666f) color |= 0x44; else if (r > 0.333f) color |= 0x4;
    if (g > 0.666f) color |= 0x22; else if (g > 0.333f) color |= 0x2;
    if (b > 0.666f) color |= 0x11; else if (b > 0.333f) color |= 0x1;

    // set char info
    character = UINT(luminance * length);
    buffer.pCharInfo[index] = { (WCHAR)ascii[max(min(character, sizeof(ascii)), 0)], color };
};

void Console::readA(PFN_WIN32ConsoleInputCallback callback)
{
	// read console input (ascii)
	WIN32ReadConsoleInstanceInputA(&instance, callback);
};

void Console::readW(PFN_WIN32ConsoleInputCallback callback)
{
	// read console input (unicode)
	WIN32ReadConsoleInstanceInputW(&instance, callback);
};

void Console::writeA(const COORD& coord, SMALL_RECT& region)
{
	// write console output (ascii)
	WIN32WriteConsoleBufferA(&instance, &buffer, coord, &region);
};

void Console::writeW(const COORD& coord, SMALL_RECT& region)
{
	// write console output (unicode)
	WIN32WriteConsoleBufferW(&instance, &buffer, coord, &region);
};

void Console::attributes(const UINT& index, const WORD& data)
{
	// set console buffer attributes
	WIN32SetConsoleBufferAttributes(&buffer, index, data);
};

void Console::background(const UINT& index, const CHAR& data)
{
	// set console buffer background
	WIN32SetConsoleBufferBackground(&buffer, index, data);
};

void Console::foreground(const UINT& index, const CHAR& data)
{
	// set console buffer foreground
	WIN32SetConsoleBufferForeground(&buffer, index, data);
};

void Console::characterA(const UINT& index, const CHAR& data)
{
	// set console buffer character (ascii)
	WIN32SetConsoleBufferCharacterA(&buffer, index, data);
};

void Console::characterW(const UINT& index, const WCHAR& data)
{
	// set console buffer character (unicode)
	WIN32SetConsoleBufferCharacterW(&buffer, index, data);
};