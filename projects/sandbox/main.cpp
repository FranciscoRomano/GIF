// #define bool int
// #define true 1
// #define false 0

#include <GIF.h>

#include <string.h>
#include "Console.h"

bool isRunning = true;
const UINT width = 80;
const UINT height = 80;
const COORD coord = { 0, 0 };
const FLOAT deltaX = 1.0f / (width - 1.0f);
const FLOAT deltaY = 1.0f / (height - 1.0f);
SMALL_RECT region = { 0, 0, width, height };

Console console { width, height };

template<typename T> T clamp(T v, T a, T b)
{
	return v < a ? a : v > b ? b : v;
};

void input_callback(INPUT_RECORD e)
{
	switch (e.EventType)
	{
		case KEY_EVENT:
			if (e.Event.KeyEvent.wVirtualKeyCode == VK_ESCAPE)
				isRunning = e.Event.KeyEvent.bKeyDown ? true : false;
			else switch (e.Event.KeyEvent.uChar.AsciiChar)
			{
				case '1':
					for (UINT y = 0; y < height; y++)
						for (UINT x = 0; x < width; x++)
							console.pixel(y * width + x, deltaX * x, deltaY * y, 1.0f);		
					console.writeA(coord, region);
					break;
				case '2':
					for (UINT y = 0; y < height; y++)
						for (UINT x = 0; x < width; x++)
							console.pixel(y * width + x, 1.0f, deltaX * x, deltaY * y);
					console.writeA(coord, region);
					break;
				case '3':
					for (UINT y = 0; y < height; y++)
						for (UINT x = 0; x < width; x++)
							console.pixel(y * width + x, deltaY * y, 1.0f, deltaX * x);
					console.writeA(coord, region);
					break;
			}
			break;
		default:
			break;
	}
}


int main(int argc, char** argv)
{
	for (UINT y = 0; y < height; y++)
		for (UINT x = 0; x < width; x++)
			console.pixel(y * width + x, deltaX * x, deltaY * y, 1.0f);
	console.writeA(coord, region);
	console.flush();
	
	while (isRunning)
	{
		console.readA(input_callback);
	}
	
	console.writeA(coord, region);

	Sleep(1000);

	return 0;
}