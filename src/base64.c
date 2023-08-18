#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#define MTRP_B64_ERROR (-(size_t)1u)
#define MTRP_B64_PADDING_OPTIONAL 0
#define MTRP_B64_PADDING_MANDATORY 1
#define MTRP_B64_PADDING_FORBIDDEN 2

#ifndef MTRP_B64_CUSTOM_CONFIG

    #undef MTRP_B64_62
    #undef MTRP_B64_63
    #undef MTRP_B64_ENCODE
    #undef MTRP_B64_DECODE
    #undef MTRP_B64_CALC_ENC
    #undef MTRP_B64_CALC_DEC
    #undef MTRP_B64_DT

    #define MTRP_B64_62 '+'
    #define MTRP_B64_63 '/'
    #define MTRP_B64_ENCODE mtrp_b64_encode
    #define MTRP_B64_DECODE mtrp_b64_decode

    #define MTRP_B64_DT \
    static uint32_t const dt[1024] = {\
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0xF8000000, 0x000000FC, 0x000000FC, 0x000000FC, 0xFC000000, \
    0xD0000000, 0xD4000000, 0xD8000000, 0xDC000000, 0xE0000000, 0xE4000000, 0xE8000000, 0xEC000000, 0xF0000000, 0xF4000000, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x00000000, 0x04000000, 0x08000000, 0x0C000000, 0x10000000, 0x14000000, 0x18000000, 0x1C000000, 0x20000000, 0x24000000, 0x28000000, 0x2C000000, 0x30000000, 0x34000000, 0x38000000, \
    0x3C000000, 0x40000000, 0x44000000, 0x48000000, 0x4C000000, 0x50000000, 0x54000000, 0x58000000, 0x5C000000, 0x60000000, 0x64000000, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x68000000, 0x6C000000, 0x70000000, 0x74000000, 0x78000000, 0x7C000000, 0x80000000, 0x84000000, 0x88000000, 0x8C000000, 0x90000000, 0x94000000, 0x98000000, 0x9C000000, 0xA0000000, \
    0xA4000000, 0xA8000000, 0xAC000000, 0xB0000000, 0xB4000000, 0xB8000000, 0xBC000000, 0xC0000000, 0xC4000000, 0xC8000000, 0xCC000000, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x03E00000, 0x000000FC, 0x000000FC, 0x000000FC, 0x03F00000, \
    0x03400000, 0x03500000, 0x03600000, 0x03700000, 0x03800000, 0x03900000, 0x03A00000, 0x03B00000, 0x03C00000, 0x03D00000, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x00000000, 0x00100000, 0x00200000, 0x00300000, 0x00400000, 0x00500000, 0x00600000, 0x00700000, 0x00800000, 0x00900000, 0x00A00000, 0x00B00000, 0x00C00000, 0x00D00000, 0x00E00000, \
    0x00F00000, 0x01000000, 0x01100000, 0x01200000, 0x01300000, 0x01400000, 0x01500000, 0x01600000, 0x01700000, 0x01800000, 0x01900000, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x01A00000, 0x01B00000, 0x01C00000, 0x01D00000, 0x01E00000, 0x01F00000, 0x02000000, 0x02100000, 0x02200000, 0x02300000, 0x02400000, 0x02500000, 0x02600000, 0x02700000, 0x02800000, \
    0x02900000, 0x02A00000, 0x02B00000, 0x02C00000, 0x02D00000, 0x02E00000, 0x02F00000, 0x03000000, 0x03100000, 0x03200000, 0x03300000, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000F8000, 0x000000FC, 0x000000FC, 0x000000FC, 0x000FC000, \
    0x000D0000, 0x000D4000, 0x000D8000, 0x000DC000, 0x000E0000, 0x000E4000, 0x000E8000, 0x000EC000, 0x000F0000, 0x000F4000, 0x000000FC, 0x000000FC, 0x000000FC, 0x00000002, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x00000000, 0x00004000, 0x00008000, 0x0000C000, 0x00010000, 0x00014000, 0x00018000, 0x0001C000, 0x00020000, 0x00024000, 0x00028000, 0x0002C000, 0x00030000, 0x00034000, 0x00038000, \
    0x0003C000, 0x00040000, 0x00044000, 0x00048000, 0x0004C000, 0x00050000, 0x00054000, 0x00058000, 0x0005C000, 0x00060000, 0x00064000, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x00068000, 0x0006C000, 0x00070000, 0x00074000, 0x00078000, 0x0007C000, 0x00080000, 0x00084000, 0x00088000, 0x0008C000, 0x00090000, 0x00094000, 0x00098000, 0x0009C000, 0x000A0000, \
    0x000A4000, 0x000A8000, 0x000AC000, 0x000B0000, 0x000B4000, 0x000B8000, 0x000BC000, 0x000C0000, 0x000C4000, 0x000C8000, 0x000CC000, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x00003E00, 0x000000FC, 0x000000FC, 0x000000FC, 0x00003F00, \
    0x00003400, 0x00003500, 0x00003600, 0x00003700, 0x00003800, 0x00003900, 0x00003A00, 0x00003B00, 0x00003C00, 0x00003D00, 0x000000FC, 0x000000FC, 0x000000FC, 0x00000001, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x00000000, 0x00000100, 0x00000200, 0x00000300, 0x00000400, 0x00000500, 0x00000600, 0x00000700, 0x00000800, 0x00000900, 0x00000A00, 0x00000B00, 0x00000C00, 0x00000D00, 0x00000E00, \
    0x00000F00, 0x00001000, 0x00001100, 0x00001200, 0x00001300, 0x00001400, 0x00001500, 0x00001600, 0x00001700, 0x00001800, 0x00001900, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x00001A00, 0x00001B00, 0x00001C00, 0x00001D00, 0x00001E00, 0x00001F00, 0x00002000, 0x00002100, 0x00002200, 0x00002300, 0x00002400, 0x00002500, 0x00002600, 0x00002700, 0x00002800, \
    0x00002900, 0x00002A00, 0x00002B00, 0x00002C00, 0x00002D00, 0x00002E00, 0x00002F00, 0x00003000, 0x00003100, 0x00003200, 0x00003300, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, \
    0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC, 0x000000FC  \
    };
    
#endif

typedef uint8_t u8;
typedef uint32_t u32;

static uint8_t const et[64] = {
'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 
'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f', 
'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 
'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', MTRP_B64_62, MTRP_B64_63
};

MTRP_B64_DT

void MTRP_B64_ENCODE(void const* const input_beg, void const* const input_end, void *const output, int pd)
{
    u8      *       out         = output;
    u8 const*       i           = input_beg;
    u8 const* const end         = input_end;
    u8 const* const aligned_end = end - ((end - i) % 3u);

    for (; i < aligned_end; i += 3u)
    { /*                     ~~~~~~~~~~~   ~~~~~~~~~~~   ~~~~~~~~~~~ */
        *out++ = et[0x3Fu & (i[0u] >> 2u                            )];
        *out++ = et[0x3Fu & (i[0u] << 4u | i[1u] >> 4u              )];
        *out++ = et[0x3Fu & (              i[1u] << 2u | i[2u] >> 6u)];
        *out++ = et[0x3Fu & (                            i[2u]      )];
    } /*                     ~~~~~~~~~~~   ~~~~~~~~~~~   ~~~~~~~~~~~  */

    /* 0x3Fu = 0b0011'1111u */

    switch (end - i)
    {
        case 1:
            *out++ = et[0x3Fu & (i[0u] >> 2u)];
            *out++ = et[0x3Fu & (i[0u] << 4u)];
            if (pd == MTRP_B64_PADDING_MANDATORY) {
            *out++ = '=';
            *out++ = '=';
            }
            break;
        case 2:
            *out++ = et[0x3Fu & (i[0u] >> 2u              )];
            *out++ = et[0x3Fu & (i[0u] << 4u | i[1u] >> 4u)];
            *out++ = et[0x3Fu & (              i[1u] << 2u)];
            if (pd == MTRP_B64_PADDING_MANDATORY) {
            *out++ = '=';
            }
            break;
    }
}

bool MTRP_B64_DECODE(void const* const input_beg, void const* const input_end, void *const output, int)
{
    u8       *      out           = output;
    u8 const *      i             = input_beg;
    u8 const *const end           = input_end;
    u8 const *const aligned_end = end - ((end - i) % 4u);
    
    u8 tag;
    u32 dword;
    
    for (; i < aligned_end; i += 4u)
    {
        dword = dt[  0u + i[0u]] | 
                dt[256u + i[1u]] | 
                dt[512u + i[2u]] | 
                dt[768u + i[3u]];
        tag = (u8)dword;
        
        if (tag != 0u)
            break;
        
        *out++ = (u8)(dword >> 24u);
        *out++ = (u8)(dword >> 16u);
        *out++ = (u8)(dword >>  8u);
    }

    size_t const modulo = end - i;
    if (modulo > 4u)
        return false;

    /* 0x03u = 0b0000'0011u
       0x02u = 0b0000'0010u
       0x01u = 0b0000'0001u */
    
    switch (modulo)
    {
        case 0u: return true;  /* ABCD  (ok) */
        case 1u: return false; /* ABCDE (no) */

        case 2u: dword = dt[  0u + i[0u]] | 
                         dt[256u + i[1u]]; 
                 tag = (u8)dword | 0x03u;
                 break;

        case 3u: dword = dt[  0u + i[0u]] |
                         dt[256u + i[1u]] |
                         dt[512u + i[2u]]; 
                 tag = (u8)dword | 0x01u;
                 break;

        case 4u: break; /* can only occur if "tag != 0u", see the 'for' loop above */
    }

    if (tag > 0x03u || tag == 0x02u)
        return false;
    
    bool const first_pad = (tag & 0x02u);  /* AA=A */
    bool const second_pad = (tag & 0x01u); /* AAA= */

    *out++ = (u8)(dword >> 24u);
    if (!first_pad) *out++ = (u8)(dword >> 16u);
    if (!second_pad) *out++ = (u8)(dword >>  8u);

    return true;
}
