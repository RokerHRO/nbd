#include "ctprint.h"
#include <stdio.h>

static const char* const ansi_colors[4] =
	{
		"\033[0m",
		"\033[0;31m",
		"\033[0;7m",
		"\033[31;7m"
	};


// print a string to stdout; non-printing/non-ASCII octets with ANSI color codes:
//
// 0x00 ... 0x1F:  red '@' ... '_'  (like control codes)
// 0x20 ... 0x7E   normal
// 0x7F            red '?'
// 0x80 ... 0x9F   inverse red '@' ... '_'
// 0xA0 ... 0xFE   inverse
// 0xFF            inverse red '?'
int ctprint(const char* string, int length)
{
	int old_mode = 0;
	int mode = 0;
	
	for(const char* p = string; p < string+length; ++p)
	{
		const unsigned char c = (unsigned char)*p;
		char pc = '\0';
		if(c<=0x1F)
		{
			mode = 1;
			pc = c + '@';
		}else if(c<=0x7E)
		{
			mode = 0;
			pc = c;
		}else if(c==0x7f)
		{
			mode = 1;
			pc = '?';
		}else if(c<=0x9F)
		{
			mode = 3;
			pc = c - 0x80 + '@';
		}else if(c<=0xFE)
		{
			mode = 2;
			pc = c - 0x80;
		}else if(c==0xFF)
		{
			mode = 3;
			pc = '?';
		}else
		{
			return -1;
		}
		
		if(mode != old_mode)
		{
			fputs(ansi_colors[mode], stdout);
			old_mode = mode;
		}
		
		putchar(pc);
	}
	return length;
}


char buffer[16] = { '\0' };

int main()
{
	for(unsigned u=0; u<256; ++u)
	{
		snprintf(buffer,15, " %c ", u);
		ctprint(buffer, 3);
		if(u%16 == 15)
		{
			putchar('\n');
		}
	}
}
