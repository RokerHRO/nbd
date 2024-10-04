#ifndef CT_PRINT_H
#define CT_PRINT_H

// print a string to stdout; non-printing/non-ASCII octets with ANSI color codes:
//
// 0x00 ... 0x1F:  red '@' ... '_'  (like control codes)
// 0x20 ... 0x7E   normal
// 0x7F            red '?'
// 0x80 ... 0x9F   inverse red '@' ... '_'
// 0xA0 ... 0xFE   inverse
// 0xFF            inverse red '?'
int ctprint(const char* string, int length);

#endif // CT_PRINT_H
