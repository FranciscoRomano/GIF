#pragma once
#include <WIN32ConsoleBuffer.h>
#include <WIN32ConsoleInstance.h>
#include <WIN32ConsoleProperties.h>


class Console
{
protected:
    WIN32ConsoleBuffer buffer;
    WIN32ConsoleInstance instance;
    WIN32ConsoleProperties properties[2];
public:
    virtual ~Console();
    Console(const UINT& width, const UINT& height);
    void flush();
    void pixel(const UINT& index, const FLOAT& r, const FLOAT& g, const FLOAT& b);
    void readA(PFN_WIN32ConsoleInputCallback callback);
    void readW(PFN_WIN32ConsoleInputCallback callback);
    void writeA(const COORD& coord, SMALL_RECT& region);
    void writeW(const COORD& coord, SMALL_RECT& region);
    void attributes(const UINT& index, const WORD& data);
    void background(const UINT& index, const CHAR& data);
    void foreground(const UINT& index, const CHAR& data);
    void characterA(const UINT& index, const CHAR& data);
    void characterW(const UINT& index, const WCHAR& data);
};