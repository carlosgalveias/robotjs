#include "universal_key_typer.h"

#include <Windows.h>
#include <thread>
#include <chrono>
#include <string>

std::u16string convertString(const char *str)
{
    std::u16string u16_string = u"";

    unsigned short c;
    unsigned short c1;
    unsigned short c2;
    unsigned short c3;
    unsigned long n;

    while (*str != '\0')
    {
        c = *str++;

        // warning, the following utf8 decoder
        // doesn't perform validation
        if (c <= 0x7F)
        {
            // 0xxxxxxx one byte
            n = c;
        }
        else if ((c & 0xE0) == 0xC0)
        {
            // 110xxxxx two bytes
            c1 = (*str++) & 0x3F;
            n = ((c & 0x1F) << 6) | c1;
        }
        else if ((c & 0xF0) == 0xE0)
        {
            // 1110xxxx three bytes
            c1 = (*str++) & 0x3F;
            c2 = (*str++) & 0x3F;
            n = ((c & 0x0F) << 12) | (c1 << 6) | c2;
        }
        else if ((c & 0xF8) == 0xF0)
        {
            // 11110xxx four bytes
            c1 = (*str++) & 0x3F;
            c2 = (*str++) & 0x3F;
            c3 = (*str++) & 0x3F;
            n = ((c & 0x07) << 18) | (c1 << 12) | (c2 << 6) | c3;
        }

        u16_string += n;
    }

    return u16_string;
}

void typeChar(char16_t c1)
{
    INPUT in1;
    in1.type = INPUT_KEYBOARD;
    in1.ki.wVk = 0;
    in1.ki.wScan = c1;
    in1.ki.time = 0;
    in1.ki.dwFlags = KEYEVENTF_UNICODE;
    in1.ki.dwExtraInfo = 0;

    INPUT i[] = {in1};
    SendInput(1, i, sizeof(INPUT));
}

void typeText(const char *str)
{
    for (char16_t c16 : convertString(str))
        typeChar(c16);
}

void typeTextDelayed(char *str, size_t milliseconds)
{
    for (char16_t c16 : convertString(str))
    {
        typeChar(c16);
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }
}