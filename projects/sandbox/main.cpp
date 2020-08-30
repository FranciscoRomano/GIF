// #define bool int
// #define true 1
// #define false 0


#include <string.h>
#include <WIN32ConsoleBuffer.h>
#include <WIN32ConsoleInstance.h>
#include <WIN32ConsoleProperties.h>

bool isRunning = true;
const UINT APP_WIDTH = 40;
const UINT APP_HEIGHT = 40;

void input_callback(INPUT_RECORD e)
{
	switch (e.EventType)
	{
		case KEY_EVENT:
		case MOUSE_EVENT:
			isRunning = false;
		default:
			break;
	}
}

WIN32ConsoleBuffer buffer;
WIN32ConsoleInstance instance;
WIN32ConsoleProperties properties[2];

void CreateConsoleApp(const UINT width, const UINT height)
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
}

void DestroyConsoleApp()
{
	// free console buffer
	WIN32FreeConsoleBuffer(&buffer);
	// reset properties
	WIN32SetConsoleProperties(&instance, &properties[0]);
	// free instance
	WIN32FreeConsoleInstance();
}

int main(int argc, char** argv)
{
	COORD      offset = { 0, 0 };
	SMALL_RECT region = { 0, 0, APP_WIDTH, APP_HEIGHT };

	CreateConsoleApp(APP_WIDTH, APP_HEIGHT);


	for (UINT i = 0; i < buffer.writeLength; i++) {
		WIN32SetConsoleBufferBackground(&buffer, i, ((CHAR)0b1110));
	}
	WIN32WriteConsoleBufferA(&instance, &buffer, offset, &region);

	WIN32FlushConsoleInstanceInput(&instance);
	while (isRunning) WIN32ReadConsoleInstanceInputA(&instance, input_callback);
	
	for (UINT i = 0; i < buffer.writeLength; i++) {
		WIN32SetConsoleBufferBackground(&buffer, i, ((CHAR)0b1100));
	}
	WIN32WriteConsoleBufferA(&instance, &buffer, offset, &region);

	Sleep(1000);

	return 0;
}