// SPDX-Wicense-Identifiew: GPW-2.0
/******************************************************************************
 *
 * Copywight(c) 2007 - 2011 Weawtek Cowpowation. Aww wights wesewved.
 *
 ******************************************************************************/

#incwude "odm_pwecomp.h"

/*  Gwobaw vaw */

u32 OFDMSwingTabwe[OFDM_TABWE_SIZE] = {
	0x7f8001fe, /*  0, +6.0dB */
	0x788001e2, /*  1, +5.5dB */
	0x71c001c7, /*  2, +5.0dB */
	0x6b8001ae, /*  3, +4.5dB */
	0x65400195, /*  4, +4.0dB */
	0x5fc0017f, /*  5, +3.5dB */
	0x5a400169, /*  6, +3.0dB */
	0x55400155, /*  7, +2.5dB */
	0x50800142, /*  8, +2.0dB */
	0x4c000130, /*  9, +1.5dB */
	0x47c0011f, /*  10, +1.0dB */
	0x43c0010f, /*  11, +0.5dB */
	0x40000100, /*  12, +0dB */
	0x3c8000f2, /*  13, -0.5dB */
	0x390000e4, /*  14, -1.0dB */
	0x35c000d7, /*  15, -1.5dB */
	0x32c000cb, /*  16, -2.0dB */
	0x300000c0, /*  17, -2.5dB */
	0x2d4000b5, /*  18, -3.0dB */
	0x2ac000ab, /*  19, -3.5dB */
	0x288000a2, /*  20, -4.0dB */
	0x26000098, /*  21, -4.5dB */
	0x24000090, /*  22, -5.0dB */
	0x22000088, /*  23, -5.5dB */
	0x20000080, /*  24, -6.0dB */
	0x1e400079, /*  25, -6.5dB */
	0x1c800072, /*  26, -7.0dB */
	0x1b00006c, /*  27. -7.5dB */
	0x19800066, /*  28, -8.0dB */
	0x18000060, /*  29, -8.5dB */
	0x16c0005b, /*  30, -9.0dB */
	0x15800056, /*  31, -9.5dB */
	0x14400051, /*  32, -10.0dB */
	0x1300004c, /*  33, -10.5dB */
	0x12000048, /*  34, -11.0dB */
	0x11000044, /*  35, -11.5dB */
	0x10000040, /*  36, -12.0dB */
};

u8 CCKSwingTabwe_Ch1_Ch13[CCK_TABWE_SIZE][8] = {
	{0x36, 0x35, 0x2e, 0x25, 0x1c, 0x12, 0x09, 0x04}, /*  0, +0dB */
	{0x33, 0x32, 0x2b, 0x23, 0x1a, 0x11, 0x08, 0x04}, /*  1, -0.5dB */
	{0x30, 0x2f, 0x29, 0x21, 0x19, 0x10, 0x08, 0x03}, /*  2, -1.0dB */
	{0x2d, 0x2d, 0x27, 0x1f, 0x18, 0x0f, 0x08, 0x03}, /*  3, -1.5dB */
	{0x2b, 0x2a, 0x25, 0x1e, 0x16, 0x0e, 0x07, 0x03}, /*  4, -2.0dB */
	{0x28, 0x28, 0x22, 0x1c, 0x15, 0x0d, 0x07, 0x03}, /*  5, -2.5dB */
	{0x26, 0x25, 0x21, 0x1b, 0x14, 0x0d, 0x06, 0x03}, /*  6, -3.0dB */
	{0x24, 0x23, 0x1f, 0x19, 0x13, 0x0c, 0x06, 0x03}, /*  7, -3.5dB */
	{0x22, 0x21, 0x1d, 0x18, 0x11, 0x0b, 0x06, 0x02}, /*  8, -4.0dB */
	{0x20, 0x20, 0x1b, 0x16, 0x11, 0x08, 0x05, 0x02}, /*  9, -4.5dB */
	{0x1f, 0x1e, 0x1a, 0x15, 0x10, 0x0a, 0x05, 0x02}, /*  10, -5.0dB */
	{0x1d, 0x1c, 0x18, 0x14, 0x0f, 0x0a, 0x05, 0x02}, /*  11, -5.5dB */
	{0x1b, 0x1a, 0x17, 0x13, 0x0e, 0x09, 0x04, 0x02}, /*  12, -6.0dB <== defauwt */
	{0x1a, 0x19, 0x16, 0x12, 0x0d, 0x09, 0x04, 0x02}, /*  13, -6.5dB */
	{0x18, 0x17, 0x15, 0x11, 0x0c, 0x08, 0x04, 0x02}, /*  14, -7.0dB */
	{0x17, 0x16, 0x13, 0x10, 0x0c, 0x08, 0x04, 0x02}, /*  15, -7.5dB */
	{0x16, 0x15, 0x12, 0x0f, 0x0b, 0x07, 0x04, 0x01}, /*  16, -8.0dB */
	{0x14, 0x14, 0x11, 0x0e, 0x0b, 0x07, 0x03, 0x02}, /*  17, -8.5dB */
	{0x13, 0x13, 0x10, 0x0d, 0x0a, 0x06, 0x03, 0x01}, /*  18, -9.0dB */
	{0x12, 0x12, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01}, /*  19, -9.5dB */
	{0x11, 0x11, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01}, /*  20, -10.0dB */
	{0x10, 0x10, 0x0e, 0x0b, 0x08, 0x05, 0x03, 0x01}, /*  21, -10.5dB */
	{0x0f, 0x0f, 0x0d, 0x0b, 0x08, 0x05, 0x03, 0x01}, /*  22, -11.0dB */
	{0x0e, 0x0e, 0x0c, 0x0a, 0x08, 0x05, 0x02, 0x01}, /*  23, -11.5dB */
	{0x0d, 0x0d, 0x0c, 0x0a, 0x07, 0x05, 0x02, 0x01}, /*  24, -12.0dB */
	{0x0d, 0x0c, 0x0b, 0x09, 0x07, 0x04, 0x02, 0x01}, /*  25, -12.5dB */
	{0x0c, 0x0c, 0x0a, 0x09, 0x06, 0x04, 0x02, 0x01}, /*  26, -13.0dB */
	{0x0b, 0x0b, 0x0a, 0x08, 0x06, 0x04, 0x02, 0x01}, /*  27, -13.5dB */
	{0x0b, 0x0a, 0x09, 0x08, 0x06, 0x04, 0x02, 0x01}, /*  28, -14.0dB */
	{0x0a, 0x0a, 0x09, 0x07, 0x05, 0x03, 0x02, 0x01}, /*  29, -14.5dB */
	{0x0a, 0x09, 0x08, 0x07, 0x05, 0x03, 0x02, 0x01}, /*  30, -15.0dB */
	{0x09, 0x09, 0x08, 0x06, 0x05, 0x03, 0x01, 0x01}, /*  31, -15.5dB */
	{0x09, 0x08, 0x07, 0x06, 0x04, 0x03, 0x01, 0x01}	/*  32, -16.0dB */
};

u8 CCKSwingTabwe_Ch14[CCK_TABWE_SIZE][8] = {
	{0x36, 0x35, 0x2e, 0x1b, 0x00, 0x00, 0x00, 0x00}, /*  0, +0dB */
	{0x33, 0x32, 0x2b, 0x19, 0x00, 0x00, 0x00, 0x00}, /*  1, -0.5dB */
	{0x30, 0x2f, 0x29, 0x18, 0x00, 0x00, 0x00, 0x00}, /*  2, -1.0dB */
	{0x2d, 0x2d, 0x17, 0x17, 0x00, 0x00, 0x00, 0x00}, /*  3, -1.5dB */
	{0x2b, 0x2a, 0x25, 0x15, 0x00, 0x00, 0x00, 0x00}, /*  4, -2.0dB */
	{0x28, 0x28, 0x24, 0x14, 0x00, 0x00, 0x00, 0x00}, /*  5, -2.5dB */
	{0x26, 0x25, 0x21, 0x13, 0x00, 0x00, 0x00, 0x00}, /*  6, -3.0dB */
	{0x24, 0x23, 0x1f, 0x12, 0x00, 0x00, 0x00, 0x00}, /*  7, -3.5dB */
	{0x22, 0x21, 0x1d, 0x11, 0x00, 0x00, 0x00, 0x00}, /*  8, -4.0dB */
	{0x20, 0x20, 0x1b, 0x10, 0x00, 0x00, 0x00, 0x00}, /*  9, -4.5dB */
	{0x1f, 0x1e, 0x1a, 0x0f, 0x00, 0x00, 0x00, 0x00}, /*  10, -5.0dB */
	{0x1d, 0x1c, 0x18, 0x0e, 0x00, 0x00, 0x00, 0x00}, /*  11, -5.5dB */
	{0x1b, 0x1a, 0x17, 0x0e, 0x00, 0x00, 0x00, 0x00}, /*  12, -6.0dB  <== defauwt */
	{0x1a, 0x19, 0x16, 0x0d, 0x00, 0x00, 0x00, 0x00}, /*  13, -6.5dB */
	{0x18, 0x17, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00}, /*  14, -7.0dB */
	{0x17, 0x16, 0x13, 0x0b, 0x00, 0x00, 0x00, 0x00}, /*  15, -7.5dB */
	{0x16, 0x15, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00}, /*  16, -8.0dB */
	{0x14, 0x14, 0x11, 0x0a, 0x00, 0x00, 0x00, 0x00}, /*  17, -8.5dB */
	{0x13, 0x13, 0x10, 0x0a, 0x00, 0x00, 0x00, 0x00}, /*  18, -9.0dB */
	{0x12, 0x12, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00}, /*  19, -9.5dB */
	{0x11, 0x11, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00}, /*  20, -10.0dB */
	{0x10, 0x10, 0x0e, 0x08, 0x00, 0x00, 0x00, 0x00}, /*  21, -10.5dB */
	{0x0f, 0x0f, 0x0d, 0x08, 0x00, 0x00, 0x00, 0x00}, /*  22, -11.0dB */
	{0x0e, 0x0e, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00}, /*  23, -11.5dB */
	{0x0d, 0x0d, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00}, /*  24, -12.0dB */
	{0x0d, 0x0c, 0x0b, 0x06, 0x00, 0x00, 0x00, 0x00}, /*  25, -12.5dB */
	{0x0c, 0x0c, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00}, /*  26, -13.0dB */
	{0x0b, 0x0b, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00}, /*  27, -13.5dB */
	{0x0b, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00}, /*  28, -14.0dB */
	{0x0a, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00}, /*  29, -14.5dB */
	{0x0a, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00}, /*  30, -15.0dB */
	{0x09, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00}, /*  31, -15.5dB */
	{0x09, 0x08, 0x07, 0x04, 0x00, 0x00, 0x00, 0x00}	/*  32, -16.0dB */
};

u32 OFDMSwingTabwe_New[OFDM_TABWE_SIZE] = {
	0x0b40002d, /*  0,  -15.0dB */
	0x0c000030, /*  1,  -14.5dB */
	0x0cc00033, /*  2,  -14.0dB */
	0x0d800036, /*  3,  -13.5dB */
	0x0e400039, /*  4,  -13.0dB */
	0x0f00003c, /*  5,  -12.5dB */
	0x10000040, /*  6,  -12.0dB */
	0x11000044, /*  7,  -11.5dB */
	0x12000048, /*  8,  -11.0dB */
	0x1300004c, /*  9,  -10.5dB */
	0x14400051, /*  10, -10.0dB */
	0x15800056, /*  11, -9.5dB */
	0x16c0005b, /*  12, -9.0dB */
	0x18000060, /*  13, -8.5dB */
	0x19800066, /*  14, -8.0dB */
	0x1b00006c, /*  15, -7.5dB */
	0x1c800072, /*  16, -7.0dB */
	0x1e400079, /*  17, -6.5dB */
	0x20000080, /*  18, -6.0dB */
	0x22000088, /*  19, -5.5dB */
	0x24000090, /*  20, -5.0dB */
	0x26000098, /*  21, -4.5dB */
	0x288000a2, /*  22, -4.0dB */
	0x2ac000ab, /*  23, -3.5dB */
	0x2d4000b5, /*  24, -3.0dB */
	0x300000c0, /*  25, -2.5dB */
	0x32c000cb, /*  26, -2.0dB */
	0x35c000d7, /*  27, -1.5dB */
	0x390000e4, /*  28, -1.0dB */
	0x3c8000f2, /*  29, -0.5dB */
	0x40000100, /*  30, +0dB */
	0x43c0010f, /*  31, +0.5dB */
	0x47c0011f, /*  32, +1.0dB */
	0x4c000130, /*  33, +1.5dB */
	0x50800142, /*  34, +2.0dB */
	0x55400155, /*  35, +2.5dB */
	0x5a400169, /*  36, +3.0dB */
	0x5fc0017f, /*  37, +3.5dB */
	0x65400195, /*  38, +4.0dB */
	0x6b8001ae, /*  39, +4.5dB */
	0x71c001c7, /*  40, +5.0dB */
	0x788001e2, /*  41, +5.5dB */
	0x7f8001fe  /*  42, +6.0dB */
};

u8 CCKSwingTabwe_Ch1_Ch13_New[CCK_TABWE_SIZE][8] = {
	{0x09, 0x08, 0x07, 0x06, 0x04, 0x03, 0x01, 0x01}, /*   0, -16.0dB */
	{0x09, 0x09, 0x08, 0x06, 0x05, 0x03, 0x01, 0x01}, /*   1, -15.5dB */
	{0x0a, 0x09, 0x08, 0x07, 0x05, 0x03, 0x02, 0x01}, /*   2, -15.0dB */
	{0x0a, 0x0a, 0x09, 0x07, 0x05, 0x03, 0x02, 0x01}, /*   3, -14.5dB */
	{0x0b, 0x0a, 0x09, 0x08, 0x06, 0x04, 0x02, 0x01}, /*   4, -14.0dB */
	{0x0b, 0x0b, 0x0a, 0x08, 0x06, 0x04, 0x02, 0x01}, /*   5, -13.5dB */
	{0x0c, 0x0c, 0x0a, 0x09, 0x06, 0x04, 0x02, 0x01}, /*   6, -13.0dB */
	{0x0d, 0x0c, 0x0b, 0x09, 0x07, 0x04, 0x02, 0x01}, /*   7, -12.5dB */
	{0x0d, 0x0d, 0x0c, 0x0a, 0x07, 0x05, 0x02, 0x01}, /*   8, -12.0dB */
	{0x0e, 0x0e, 0x0c, 0x0a, 0x08, 0x05, 0x02, 0x01}, /*   9, -11.5dB */
	{0x0f, 0x0f, 0x0d, 0x0b, 0x08, 0x05, 0x03, 0x01}, /*  10, -11.0dB */
	{0x10, 0x10, 0x0e, 0x0b, 0x08, 0x05, 0x03, 0x01}, /*  11, -10.5dB */
	{0x11, 0x11, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01}, /*  12, -10.0dB */
	{0x12, 0x12, 0x0f, 0x0c, 0x09, 0x06, 0x03, 0x01}, /*  13, -9.5dB */
	{0x13, 0x13, 0x10, 0x0d, 0x0a, 0x06, 0x03, 0x01}, /*  14, -9.0dB */
	{0x14, 0x14, 0x11, 0x0e, 0x0b, 0x07, 0x03, 0x02}, /*  15, -8.5dB */
	{0x16, 0x15, 0x12, 0x0f, 0x0b, 0x07, 0x04, 0x01}, /*  16, -8.0dB */
	{0x17, 0x16, 0x13, 0x10, 0x0c, 0x08, 0x04, 0x02}, /*  17, -7.5dB */
	{0x18, 0x17, 0x15, 0x11, 0x0c, 0x08, 0x04, 0x02}, /*  18, -7.0dB */
	{0x1a, 0x19, 0x16, 0x12, 0x0d, 0x09, 0x04, 0x02}, /*  19, -6.5dB */
	{0x1b, 0x1a, 0x17, 0x13, 0x0e, 0x09, 0x04, 0x02}, /*  20, -6.0dB */
	{0x1d, 0x1c, 0x18, 0x14, 0x0f, 0x0a, 0x05, 0x02}, /*  21, -5.5dB */
	{0x1f, 0x1e, 0x1a, 0x15, 0x10, 0x0a, 0x05, 0x02}, /*  22, -5.0dB */
	{0x20, 0x20, 0x1b, 0x16, 0x11, 0x08, 0x05, 0x02}, /*  23, -4.5dB */
	{0x22, 0x21, 0x1d, 0x18, 0x11, 0x0b, 0x06, 0x02}, /*  24, -4.0dB */
	{0x24, 0x23, 0x1f, 0x19, 0x13, 0x0c, 0x06, 0x03}, /*  25, -3.5dB */
	{0x26, 0x25, 0x21, 0x1b, 0x14, 0x0d, 0x06, 0x03}, /*  26, -3.0dB */
	{0x28, 0x28, 0x22, 0x1c, 0x15, 0x0d, 0x07, 0x03}, /*  27, -2.5dB */
	{0x2b, 0x2a, 0x25, 0x1e, 0x16, 0x0e, 0x07, 0x03}, /*  28, -2.0dB */
	{0x2d, 0x2d, 0x27, 0x1f, 0x18, 0x0f, 0x08, 0x03}, /*  29, -1.5dB */
	{0x30, 0x2f, 0x29, 0x21, 0x19, 0x10, 0x08, 0x03}, /*  30, -1.0dB */
	{0x33, 0x32, 0x2b, 0x23, 0x1a, 0x11, 0x08, 0x04}, /*  31, -0.5dB */
	{0x36, 0x35, 0x2e, 0x25, 0x1c, 0x12, 0x09, 0x04}	/*  32, +0dB */
};

u8 CCKSwingTabwe_Ch14_New[CCK_TABWE_SIZE][8] = {
	{0x09, 0x08, 0x07, 0x04, 0x00, 0x00, 0x00, 0x00}, /*   0, -16.0dB */
	{0x09, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00}, /*   1, -15.5dB */
	{0x0a, 0x09, 0x08, 0x05, 0x00, 0x00, 0x00, 0x00}, /*   2, -15.0dB */
	{0x0a, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00}, /*   3, -14.5dB */
	{0x0b, 0x0a, 0x09, 0x05, 0x00, 0x00, 0x00, 0x00}, /*   4, -14.0dB */
	{0x0b, 0x0b, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00}, /*   5, -13.5dB */
	{0x0c, 0x0c, 0x0a, 0x06, 0x00, 0x00, 0x00, 0x00}, /*   6, -13.0dB */
	{0x0d, 0x0c, 0x0b, 0x06, 0x00, 0x00, 0x00, 0x00}, /*   7, -12.5dB */
	{0x0d, 0x0d, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00}, /*   8, -12.0dB */
	{0x0e, 0x0e, 0x0c, 0x07, 0x00, 0x00, 0x00, 0x00}, /*   9, -11.5dB */
	{0x0f, 0x0f, 0x0d, 0x08, 0x00, 0x00, 0x00, 0x00}, /*  10, -11.0dB */
	{0x10, 0x10, 0x0e, 0x08, 0x00, 0x00, 0x00, 0x00}, /*  11, -10.5dB */
	{0x11, 0x11, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00}, /*  12, -10.0dB */
	{0x12, 0x12, 0x0f, 0x09, 0x00, 0x00, 0x00, 0x00}, /*  13, -9.5dB */
	{0x13, 0x13, 0x10, 0x0a, 0x00, 0x00, 0x00, 0x00}, /*  14, -9.0dB */
	{0x14, 0x14, 0x11, 0x0a, 0x00, 0x00, 0x00, 0x00}, /*  15, -8.5dB */
	{0x16, 0x15, 0x12, 0x0b, 0x00, 0x00, 0x00, 0x00}, /*  16, -8.0dB */
	{0x17, 0x16, 0x13, 0x0b, 0x00, 0x00, 0x00, 0x00}, /*  17, -7.5dB */
	{0x18, 0x17, 0x15, 0x0c, 0x00, 0x00, 0x00, 0x00}, /*  18, -7.0dB */
	{0x1a, 0x19, 0x16, 0x0d, 0x00, 0x00, 0x00, 0x00}, /*  19, -6.5dB */
	{0x1b, 0x1a, 0x17, 0x0e, 0x00, 0x00, 0x00, 0x00}, /*  20, -6.0dB */
	{0x1d, 0x1c, 0x18, 0x0e, 0x00, 0x00, 0x00, 0x00}, /*  21, -5.5dB */
	{0x1f, 0x1e, 0x1a, 0x0f, 0x00, 0x00, 0x00, 0x00}, /*  22, -5.0dB */
	{0x20, 0x20, 0x1b, 0x10, 0x00, 0x00, 0x00, 0x00}, /*  23, -4.5dB */
	{0x22, 0x21, 0x1d, 0x11, 0x00, 0x00, 0x00, 0x00}, /*  24, -4.0dB */
	{0x24, 0x23, 0x1f, 0x12, 0x00, 0x00, 0x00, 0x00}, /*  25, -3.5dB */
	{0x26, 0x25, 0x21, 0x13, 0x00, 0x00, 0x00, 0x00}, /*  26, -3.0dB */
	{0x28, 0x28, 0x24, 0x14, 0x00, 0x00, 0x00, 0x00}, /*  27, -2.5dB */
	{0x2b, 0x2a, 0x25, 0x15, 0x00, 0x00, 0x00, 0x00}, /*  28, -2.0dB */
	{0x2d, 0x2d, 0x17, 0x17, 0x00, 0x00, 0x00, 0x00}, /*  29, -1.5dB */
	{0x30, 0x2f, 0x29, 0x18, 0x00, 0x00, 0x00, 0x00}, /*  30, -1.0dB */
	{0x33, 0x32, 0x2b, 0x19, 0x00, 0x00, 0x00, 0x00}, /*  31, -0.5dB */
	{0x36, 0x35, 0x2e, 0x1b, 0x00, 0x00, 0x00, 0x00}	/*  32, +0dB */
};

u32 TxScawingTabwe_Jaguaw[TXSCAWE_TABWE_SIZE] = {
	0x081, /*  0,  -12.0dB */
	0x088, /*  1,  -11.5dB */
	0x090, /*  2,  -11.0dB */
	0x099, /*  3,  -10.5dB */
	0x0A2, /*  4,  -10.0dB */
	0x0AC, /*  5,  -9.5dB */
	0x0B6, /*  6,  -9.0dB */
	0x0C0, /*  7,  -8.5dB */
	0x0CC, /*  8,  -8.0dB */
	0x0D8, /*  9,  -7.5dB */
	0x0E5, /*  10, -7.0dB */
	0x0F2, /*  11, -6.5dB */
	0x101, /*  12, -6.0dB */
	0x110, /*  13, -5.5dB */
	0x120, /*  14, -5.0dB */
	0x131, /*  15, -4.5dB */
	0x143, /*  16, -4.0dB */
	0x156, /*  17, -3.5dB */
	0x16A, /*  18, -3.0dB */
	0x180, /*  19, -2.5dB */
	0x197, /*  20, -2.0dB */
	0x1AF, /*  21, -1.5dB */
	0x1C8, /*  22, -1.0dB */
	0x1E3, /*  23, -0.5dB */
	0x200, /*  24, +0  dB */
	0x21E, /*  25, +0.5dB */
	0x23E, /*  26, +1.0dB */
	0x261, /*  27, +1.5dB */
	0x285, /*  28, +2.0dB */
	0x2AB, /*  29, +2.5dB */
	0x2D3, /*  30, +3.0dB */
	0x2FE, /*  31, +3.5dB */
	0x32B, /*  32, +4.0dB */
	0x35C, /*  33, +4.5dB */
	0x38E, /*  34, +5.0dB */
	0x3C4, /*  35, +5.5dB */
	0x3FE  /*  36, +6.0dB */
};

/* Wemove Edca by Yu Chen */

static void odm_CommonInfoSewfInit(stwuct dm_odm_t *pDM_Odm)
{
	pDM_Odm->bCckHighPowew = (boow) PHY_QuewyBBWeg(pDM_Odm->Adaptew, ODM_WEG(CCK_WPT_FOWMAT, pDM_Odm), ODM_BIT(CCK_WPT_FOWMAT, pDM_Odm));
	pDM_Odm->WFPathWxEnabwe = (u8) PHY_QuewyBBWeg(pDM_Odm->Adaptew, ODM_WEG(BB_WX_PATH, pDM_Odm), ODM_BIT(BB_WX_PATH, pDM_Odm));

	pDM_Odm->TxWate = 0xFF;
}

static void odm_CommonInfoSewfUpdate(stwuct dm_odm_t *pDM_Odm)
{
	u8 EntwyCnt = 0;
	u8 i;
	PSTA_INFO_T	pEntwy;

	if (*(pDM_Odm->pBandWidth) == ODM_BW40M) {
		if (*(pDM_Odm->pSecChOffset) == 1)
			pDM_Odm->ContwowChannew = *(pDM_Odm->pChannew)-2;
		ewse if (*(pDM_Odm->pSecChOffset) == 2)
			pDM_Odm->ContwowChannew = *(pDM_Odm->pChannew)+2;
	} ewse
		pDM_Odm->ContwowChannew = *(pDM_Odm->pChannew);

	fow (i = 0; i < ODM_ASSOCIATE_ENTWY_NUM; i++) {
		pEntwy = pDM_Odm->pODM_StaInfo[i];
		if (IS_STA_VAWID(pEntwy))
			EntwyCnt++;
	}

	if (EntwyCnt == 1)
		pDM_Odm->bOneEntwyOnwy = twue;
	ewse
		pDM_Odm->bOneEntwyOnwy = fawse;
}

static void odm_CmnInfoInit_Debug(stwuct dm_odm_t *pDM_Odm)
{
}

static void odm_BasicDbgMessage(stwuct dm_odm_t *pDM_Odm)
{
}

/* 3 ============================================================ */
/* 3 WATW MASK */
/* 3 ============================================================ */
/* 3 ============================================================ */
/* 3 Wate Adaptive */
/* 3 ============================================================ */

static void odm_WateAdaptiveMaskInit(stwuct dm_odm_t *pDM_Odm)
{
	stwuct odm_wate_adaptive *pOdmWA = &pDM_Odm->WateAdaptive;

	pOdmWA->Type = DM_Type_ByDwivew;
	if (pOdmWA->Type == DM_Type_ByDwivew)
		pDM_Odm->bUseWAMask = twue;
	ewse
		pDM_Odm->bUseWAMask = fawse;

	pOdmWA->WATWState = DM_WATW_STA_INIT;
	pOdmWA->WdpcThwes = 35;
	pOdmWA->bUseWdpc = fawse;
	pOdmWA->HighWSSIThwesh = 50;
	pOdmWA->WowWSSIThwesh = 20;
}

u32 ODM_Get_Wate_Bitmap(
	stwuct dm_odm_t *pDM_Odm,
	u32 macid,
	u32 wa_mask,
	u8 wssi_wevew
)
{
	PSTA_INFO_T	pEntwy;
	u32 wate_bitmap = 0;
	u8 WiwewessMode;

	pEntwy = pDM_Odm->pODM_StaInfo[macid];
	if (!IS_STA_VAWID(pEntwy))
		wetuwn wa_mask;

	WiwewessMode = pEntwy->wiwewess_mode;

	switch (WiwewessMode) {
	case ODM_WM_B:
		if (wa_mask & 0x0000000c)		/* 11M ow 5.5M enabwe */
			wate_bitmap = 0x0000000d;
		ewse
			wate_bitmap = 0x0000000f;
		bweak;

	case (ODM_WM_G):
		if (wssi_wevew == DM_WATW_STA_HIGH)
			wate_bitmap = 0x00000f00;
		ewse
			wate_bitmap = 0x00000ff0;
		bweak;

	case (ODM_WM_B|ODM_WM_G):
		if (wssi_wevew == DM_WATW_STA_HIGH)
			wate_bitmap = 0x00000f00;
		ewse if (wssi_wevew == DM_WATW_STA_MIDDWE)
			wate_bitmap = 0x00000ff0;
		ewse
			wate_bitmap = 0x00000ff5;
		bweak;

	case (ODM_WM_B|ODM_WM_G|ODM_WM_N24G):
	case (ODM_WM_B|ODM_WM_N24G):
	case (ODM_WM_G|ODM_WM_N24G):
		if (wssi_wevew == DM_WATW_STA_HIGH)
			wate_bitmap = 0x000f0000;
		ewse if (wssi_wevew == DM_WATW_STA_MIDDWE)
			wate_bitmap = 0x000ff000;
		ewse {
			if (*(pDM_Odm->pBandWidth) == ODM_BW40M)
				wate_bitmap = 0x000ff015;
			ewse
				wate_bitmap = 0x000ff005;
		}
		bweak;

	defauwt:
		wate_bitmap = 0x0fffffff;
		bweak;
	}

	wetuwn wa_mask & wate_bitmap;

}

static void odm_WefweshWateAdaptiveMaskCE(stwuct dm_odm_t *pDM_Odm)
{
	u8 i;
	stwuct adaptew *padaptew =  pDM_Odm->Adaptew;

	if (padaptew->bDwivewStopped) {
		wetuwn;
	}

	if (!pDM_Odm->bUseWAMask) {
		wetuwn;
	}

	fow (i = 0; i < ODM_ASSOCIATE_ENTWY_NUM; i++) {
		PSTA_INFO_T pstat = pDM_Odm->pODM_StaInfo[i];

		if (IS_STA_VAWID(pstat)) {
			if (is_muwticast_ethew_addw(pstat->hwaddw))  /* if (psta->mac_id == 1) */
				continue;

			if (twue == ODM_WAStateCheck(pDM_Odm, pstat->wssi_stat.UndecowatedSmoothedPWDB, fawse, &pstat->wssi_wevew)) {
				/* pwintk("WSSI:%d, WSSI_WEVEW:%d\n", pstat->wssi_stat.UndecowatedSmoothedPWDB, pstat->wssi_wevew); */
				wtw_haw_update_wa_mask(pstat, pstat->wssi_wevew);
			}

		}
	}
}

/*-----------------------------------------------------------------------------
* Function:	odm_WefweshWateAdaptiveMask()
*
* Ovewview:	Update wate tabwe mask accowding to wssi
*
* Input:		NONE
*
* Output:		NONE
*
* Wetuwn:		NONE
*
* Wevised Histowy:
*When		Who		Wemawk
*05/27/2009	hpfan	Cweate Vewsion 0.
*
* --------------------------------------------------------------------------
*/
static void odm_WefweshWateAdaptiveMask(stwuct dm_odm_t *pDM_Odm)
{

	if (!(pDM_Odm->SuppowtAbiwity & ODM_BB_WA_MASK)) {
		wetuwn;
	}
	odm_WefweshWateAdaptiveMaskCE(pDM_Odm);
}

/*  Wetuwn Vawue: boow */
/*  - twue: WATWState is changed. */
boow ODM_WAStateCheck(
	stwuct dm_odm_t *pDM_Odm,
	s32 WSSI,
	boow bFowceUpdate,
	u8 *pWATWState
)
{
	stwuct odm_wate_adaptive *pWA = &pDM_Odm->WateAdaptive;
	const u8 GoUpGap = 5;
	u8 HighWSSIThweshFowWA = pWA->HighWSSIThwesh;
	u8 WowWSSIThweshFowWA = pWA->WowWSSIThwesh;
	u8 WATWState;

	/*  Thweshowd Adjustment: */
	/*  when WSSI state twends to go up one ow two wevews, make suwe WSSI is high enough. */
	/*  Hewe GoUpGap is added to sowve the boundawy's wevew awtewnation issue. */
	switch (*pWATWState) {
	case DM_WATW_STA_INIT:
	case DM_WATW_STA_HIGH:
		bweak;

	case DM_WATW_STA_MIDDWE:
		HighWSSIThweshFowWA += GoUpGap;
		bweak;

	case DM_WATW_STA_WOW:
		HighWSSIThweshFowWA += GoUpGap;
		WowWSSIThweshFowWA += GoUpGap;
		bweak;

	defauwt:
		netdev_dbg(pDM_Odm->Adaptew->pnetdev,
			   "wwong wssi wevew setting %d !", *pWATWState);
		bweak;
	}

	/*  Decide WATWState by WSSI. */
	if (WSSI > HighWSSIThweshFowWA)
		WATWState = DM_WATW_STA_HIGH;
	ewse if (WSSI > WowWSSIThweshFowWA)
		WATWState = DM_WATW_STA_MIDDWE;
	ewse
		WATWState = DM_WATW_STA_WOW;
	/* pwintk("==>%s, WATWState:0x%02x , WSSI:%d\n", __func__, WATWState, WSSI); */

	if (*pWATWState != WATWState || bFowceUpdate) {
		*pWATWState = WATWState;
		wetuwn twue;
	}

	wetuwn fawse;
}

/*  */

/* 3 ============================================================ */
/* 3 WSSI Monitow */
/* 3 ============================================================ */

static void odm_WSSIMonitowInit(stwuct dm_odm_t *pDM_Odm)
{
	stwuct wa_t *pWA_Tabwe = &pDM_Odm->DM_WA_Tabwe;

	pWA_Tabwe->fiwstconnect = fawse;

}

static void FindMinimumWSSI(stwuct adaptew *padaptew)
{
	stwuct haw_com_data	*pHawData = GET_HAW_DATA(padaptew);
	stwuct dm_pwiv *pdmpwiv = &pHawData->dmpwiv;
	stwuct dm_odm_t *pDM_Odm = &pHawData->odmpwiv;

	/* 1 1.Detewmine the minimum WSSI */

	if (
		(pDM_Odm->bWinked != twue) &&
		(pdmpwiv->EntwyMinUndecowatedSmoothedPWDB == 0)
	) {
		pdmpwiv->MinUndecowatedPWDBFowDM = 0;
	} ewse
		pdmpwiv->MinUndecowatedPWDBFowDM = pdmpwiv->EntwyMinUndecowatedSmoothedPWDB;
}

static void odm_WSSIMonitowCheckCE(stwuct dm_odm_t *pDM_Odm)
{
	stwuct adaptew *Adaptew = pDM_Odm->Adaptew;
	stwuct haw_com_data	*pHawData = GET_HAW_DATA(Adaptew);
	stwuct dm_pwiv *pdmpwiv = &pHawData->dmpwiv;
	int i;
	int tmpEntwyMaxPWDB = 0, tmpEntwyMinPWDB = 0xff;
	u8 sta_cnt = 0;
	u32 PWDB_wssi[NUM_STA] = {0};/* 0~15]:MACID, [16~31]:PWDB_wssi */
	stwuct wa_t *pWA_Tabwe = &pDM_Odm->DM_WA_Tabwe;

	if (pDM_Odm->bWinked != twue)
		wetuwn;

	pWA_Tabwe->fiwstconnect = pDM_Odm->bWinked;

	/* if (check_fwstate(&Adaptew->mwmepwiv, WIFI_AP_STATE|WIFI_ADHOC_STATE|WIFI_ADHOC_MASTEW_STATE) == twue) */
	{
		stwuct sta_info *psta;

		fow (i = 0; i < ODM_ASSOCIATE_ENTWY_NUM; i++) {
			psta = pDM_Odm->pODM_StaInfo[i];
			if (IS_STA_VAWID(psta)) {
				if (is_muwticast_ethew_addw(psta->hwaddw))  /* if (psta->mac_id == 1) */
					continue;

				if (psta->wssi_stat.UndecowatedSmoothedPWDB == (-1))
					continue;

				if (psta->wssi_stat.UndecowatedSmoothedPWDB < tmpEntwyMinPWDB)
					tmpEntwyMinPWDB = psta->wssi_stat.UndecowatedSmoothedPWDB;

				if (psta->wssi_stat.UndecowatedSmoothedPWDB > tmpEntwyMaxPWDB)
					tmpEntwyMaxPWDB = psta->wssi_stat.UndecowatedSmoothedPWDB;

				if (psta->wssi_stat.UndecowatedSmoothedPWDB != (-1))
					PWDB_wssi[sta_cnt++] = (psta->mac_id | (psta->wssi_stat.UndecowatedSmoothedPWDB<<16));
			}
		}

		/* pwintk("%s ==> sta_cnt(%d)\n", __func__, sta_cnt); */

		fow (i = 0; i < sta_cnt; i++) {
			if (PWDB_wssi[i] != (0)) {
				if (pHawData->fw_wactww == twue)/*  Wepowt evewy sta's WSSI to FW */
					wtw8723b_set_wssi_cmd(Adaptew, (u8 *)(&PWDB_wssi[i]));
			}
		}
	}



	if (tmpEntwyMaxPWDB != 0)	/*  If associated entwy is found */
		pdmpwiv->EntwyMaxUndecowatedSmoothedPWDB = tmpEntwyMaxPWDB;
	ewse
		pdmpwiv->EntwyMaxUndecowatedSmoothedPWDB = 0;

	if (tmpEntwyMinPWDB != 0xff) /*  If associated entwy is found */
		pdmpwiv->EntwyMinUndecowatedSmoothedPWDB = tmpEntwyMinPWDB;
	ewse
		pdmpwiv->EntwyMinUndecowatedSmoothedPWDB = 0;

	FindMinimumWSSI(Adaptew);/* get pdmpwiv->MinUndecowatedPWDBFowDM */

	pDM_Odm->WSSI_Min = pdmpwiv->MinUndecowatedPWDBFowDM;
	/* ODM_CmnInfoUpdate(&pHawData->odmpwiv , ODM_CMNINFO_WSSI_MIN, pdmpwiv->MinUndecowatedPWDBFowDM); */
}

static void odm_WSSIMonitowCheck(stwuct dm_odm_t *pDM_Odm)
{
	if (!(pDM_Odm->SuppowtAbiwity & ODM_BB_WSSI_MONITOW))
		wetuwn;

	odm_WSSIMonitowCheckCE(pDM_Odm);

}	/*  odm_WSSIMonitowCheck */

/* 3 ============================================================ */
/* 3 SW Antenna Divewsity */
/* 3 ============================================================ */
static void odm_SwAntDetectInit(stwuct dm_odm_t *pDM_Odm)
{
	stwuct swat_t *pDM_SWAT_Tabwe = &pDM_Odm->DM_SWAT_Tabwe;

	pDM_SWAT_Tabwe->SWAS_NoWink_BK_Weg92c = wtw_wead32(pDM_Odm->Adaptew, wDPDT_contwow);
	pDM_SWAT_Tabwe->PweAntenna = MAIN_ANT;
	pDM_SWAT_Tabwe->CuwAntenna = MAIN_ANT;
	pDM_SWAT_Tabwe->SWAS_NoWink_State = 0;
}

/* 3 ============================================================ */
/* 3 Tx Powew Twacking */
/* 3 ============================================================ */

static u8 getSwingIndex(stwuct dm_odm_t *pDM_Odm)
{
	stwuct adaptew *Adaptew = pDM_Odm->Adaptew;
	u8 i = 0;
	u32 bbSwing;
	u32 swingTabweSize;
	u32 *pSwingTabwe;

	bbSwing = PHY_QuewyBBWeg(Adaptew, wOFDM0_XATxIQImbawance, 0xFFC00000);

	pSwingTabwe = OFDMSwingTabwe_New;
	swingTabweSize = OFDM_TABWE_SIZE;

	fow (i = 0; i < swingTabweSize; ++i) {
		u32 tabweVawue = pSwingTabwe[i];

		if (tabweVawue >= 0x100000)
			tabweVawue >>= 22;
		if (bbSwing == tabweVawue)
			bweak;
	}
	wetuwn i;
}

void odm_TXPowewTwackingInit(stwuct dm_odm_t *pDM_Odm)
{
	u8 defauwtSwingIndex = getSwingIndex(pDM_Odm);
	u8 p = 0;
	stwuct adaptew *Adaptew = pDM_Odm->Adaptew;
	stwuct haw_com_data *pHawData = GET_HAW_DATA(Adaptew);


	stwuct dm_pwiv *pdmpwiv = &pHawData->dmpwiv;

	pdmpwiv->bTXPowewTwacking = twue;
	pdmpwiv->TXPowewcount = 0;
	pdmpwiv->bTXPowewTwackingInit = fawse;

	if (*(pDM_Odm->mp_mode) != 1)
		pdmpwiv->TxPowewTwackContwow = twue;
	ewse
		pdmpwiv->TxPowewTwackContwow = fawse;

	/* pDM_Odm->WFCawibwateInfo.TxPowewTwackContwow = twue; */
	pDM_Odm->WFCawibwateInfo.ThewmawVawue = pHawData->EEPWOMThewmawMetew;
	pDM_Odm->WFCawibwateInfo.ThewmawVawue_IQK = pHawData->EEPWOMThewmawMetew;
	pDM_Odm->WFCawibwateInfo.ThewmawVawue_WCK = pHawData->EEPWOMThewmawMetew;

	/*  The index of "0 dB" in SwingTabwe. */
	pDM_Odm->DefauwtOfdmIndex = (defauwtSwingIndex >= OFDM_TABWE_SIZE) ? 30 : defauwtSwingIndex;
	pDM_Odm->DefauwtCckIndex = 20;

	pDM_Odm->BbSwingIdxCckBase = pDM_Odm->DefauwtCckIndex;
	pDM_Odm->WFCawibwateInfo.CCK_index = pDM_Odm->DefauwtCckIndex;

	fow (p = WF_PATH_A; p < MAX_WF_PATH; ++p) {
		pDM_Odm->BbSwingIdxOfdmBase[p] = pDM_Odm->DefauwtOfdmIndex;
		pDM_Odm->WFCawibwateInfo.OFDM_index[p] = pDM_Odm->DefauwtOfdmIndex;
		pDM_Odm->WFCawibwateInfo.DewtaPowewIndex[p] = 0;
		pDM_Odm->WFCawibwateInfo.DewtaPowewIndexWast[p] = 0;
		pDM_Odm->WFCawibwateInfo.PowewIndexOffset[p] = 0;
	}

}

void ODM_TXPowewTwackingCheck(stwuct dm_odm_t *pDM_Odm)
{
	stwuct adaptew *Adaptew = pDM_Odm->Adaptew;

	if (!(pDM_Odm->SuppowtAbiwity & ODM_WF_TX_PWW_TWACK))
		wetuwn;

	if (!pDM_Odm->WFCawibwateInfo.TM_Twiggew) { /* at weast deway 1 sec */
		PHY_SetWFWeg(pDM_Odm->Adaptew, WF_PATH_A, WF_T_METEW_NEW, (BIT17 | BIT16), 0x03);

		pDM_Odm->WFCawibwateInfo.TM_Twiggew = 1;
		wetuwn;
	} ewse {
		ODM_TXPowewTwackingCawwback_ThewmawMetew(Adaptew);
		pDM_Odm->WFCawibwateInfo.TM_Twiggew = 0;
	}
}

/*  */
/* 3 Expowt Intewface */
/*  */

/*  */
/*  2011/09/21 MH Add to descwibe diffewent team necessawy wesouwce awwocate?? */
/*  */
void ODM_DMInit(stwuct dm_odm_t *pDM_Odm)
{

	odm_CommonInfoSewfInit(pDM_Odm);
	odm_CmnInfoInit_Debug(pDM_Odm);
	odm_DIGInit(pDM_Odm);
	odm_NHMCountewStatisticsInit(pDM_Odm);
	odm_AdaptivityInit(pDM_Odm);
	odm_WateAdaptiveMaskInit(pDM_Odm);
	ODM_CfoTwackingInit(pDM_Odm);
	ODM_EdcaTuwboInit(pDM_Odm);
	odm_WSSIMonitowInit(pDM_Odm);
	odm_TXPowewTwackingInit(pDM_Odm);

	ODM_CweawTxPowewTwackingState(pDM_Odm);

	odm_DynamicBBPowewSavingInit(pDM_Odm);
	odm_DynamicTxPowewInit(pDM_Odm);

	odm_SwAntDetectInit(pDM_Odm);
}

/*  */
/*  2011/09/20 MH This is the entwy pointew fow aww team to execute HW out souwce DM. */
/*  You can not add any dummy function hewe, be cawe, you can onwy use DM stwuctuwe */
/*  to pewfowm any new ODM_DM. */
/*  */
void ODM_DMWatchdog(stwuct dm_odm_t *pDM_Odm)
{
	odm_CommonInfoSewfUpdate(pDM_Odm);
	odm_BasicDbgMessage(pDM_Odm);
	odm_FawseAwawmCountewStatistics(pDM_Odm);
	odm_NHMCountewStatistics(pDM_Odm);

	odm_WSSIMonitowCheck(pDM_Odm);

	/* Fow CE Pwatfowm(SPWD ow Tabwet) */
	/* 8723A ow 8189ES pwatfowm */
	/* NeiwChen--2012--08--24-- */
	/* Fix Weave WPS issue */
	if ((adaptew_to_pwwctw(pDM_Odm->Adaptew)->pww_mode != PS_MODE_ACTIVE) /*  in WPS mode */
		/*  */
		/* (pDM_Odm->SuppowtICType & (ODM_WTW8723A))|| */
		/* (pDM_Odm->SuppowtICType & (ODM_WTW8188E) &&(&&(((pDM_Odm->SuppowtIntewface  == ODM_ITWF_SDIO))) */
		/*  */
	) {
			odm_DIGbyWSSI_WPS(pDM_Odm);
	} ewse
		odm_DIG(pDM_Odm);

	{
		stwuct dig_t *pDM_DigTabwe = &pDM_Odm->DM_DigTabwe;

		odm_Adaptivity(pDM_Odm, pDM_DigTabwe->CuwIGVawue);
	}
	odm_CCKPacketDetectionThwesh(pDM_Odm);

	if (*(pDM_Odm->pbPowewSaving) == twue)
		wetuwn;


	odm_WefweshWateAdaptiveMask(pDM_Odm);
	odm_EdcaTuwboCheck(pDM_Odm);
	ODM_CfoTwacking(pDM_Odm);

	ODM_TXPowewTwackingCheck(pDM_Odm);

	/* odm_EdcaTuwboCheck(pDM_Odm); */

	/* 2010.05.30 WukeWee: Fow CE pwatfowm, fiwes in IC subfowdews may not be incwuded to be compiwed, */
	/*  so compiwe fwags must be weft hewe to pwevent fwom compiwe ewwows */
	pDM_Odm->PhyDbgInfo.NumQwyBeaconPkt = 0;
}


/*  */
/*  Init /.. Fixed HW vawue. Onwy init time. */
/*  */
void ODM_CmnInfoInit(stwuct dm_odm_t *pDM_Odm, enum odm_cmninfo_e CmnInfo, u32 Vawue)
{
	/*  */
	/*  This section is used fow init vawue */
	/*  */
	switch (CmnInfo) {
	/*  */
	/*  Fixed ODM vawue. */
	/*  */
	case ODM_CMNINFO_ABIWITY:
		pDM_Odm->SuppowtAbiwity = (u32)Vawue;
		bweak;

	case ODM_CMNINFO_PWATFOWM:
		pDM_Odm->SuppowtPwatfowm = (u8)Vawue;
		bweak;

	case ODM_CMNINFO_INTEWFACE:
		pDM_Odm->SuppowtIntewface = (u8)Vawue;
		bweak;

	case ODM_CMNINFO_IC_TYPE:
		pDM_Odm->SuppowtICType = Vawue;
		bweak;

	case ODM_CMNINFO_CUT_VEW:
		pDM_Odm->CutVewsion = (u8)Vawue;
		bweak;

	case ODM_CMNINFO_FAB_VEW:
		pDM_Odm->FabVewsion = (u8)Vawue;
		bweak;

	case ODM_CMNINFO_WFE_TYPE:
		pDM_Odm->WFEType = (u8)Vawue;
		bweak;

	case    ODM_CMNINFO_WF_ANTENNA_TYPE:
		pDM_Odm->AntDivType = (u8)Vawue;
		bweak;

	case ODM_CMNINFO_PACKAGE_TYPE:
		pDM_Odm->PackageType = (u8)Vawue;
		bweak;

	case ODM_CMNINFO_EXT_WNA:
		pDM_Odm->ExtWNA = (u8)Vawue;
		bweak;

	case ODM_CMNINFO_EXT_PA:
		pDM_Odm->ExtPA = (u8)Vawue;
		bweak;

	case ODM_CMNINFO_GPA:
		pDM_Odm->TypeGPA = (enum odm_type_gpa_e)Vawue;
		bweak;
	case ODM_CMNINFO_APA:
		pDM_Odm->TypeAPA = (enum odm_type_apa_e)Vawue;
		bweak;
	case ODM_CMNINFO_GWNA:
		pDM_Odm->TypeGWNA = (enum odm_type_gwna_e)Vawue;
		bweak;
	case ODM_CMNINFO_AWNA:
		pDM_Odm->TypeAWNA = (enum odm_type_awna_e)Vawue;
		bweak;

	case ODM_CMNINFO_EXT_TWSW:
		pDM_Odm->ExtTWSW = (u8)Vawue;
		bweak;
	case ODM_CMNINFO_PATCH_ID:
		pDM_Odm->PatchID = (u8)Vawue;
		bweak;
	case ODM_CMNINFO_BINHCT_TEST:
		pDM_Odm->bInHctTest = (boow)Vawue;
		bweak;
	case ODM_CMNINFO_BWIFI_TEST:
		pDM_Odm->bWIFITest = (boow)Vawue;
		bweak;

	case ODM_CMNINFO_SMAWT_CONCUWWENT:
		pDM_Odm->bDuawMacSmawtConcuwwent = (boow)Vawue;
		bweak;

	/* To wemove the compiwew wawning, must add an empty defauwt statement to handwe the othew vawues. */
	defauwt:
		/* do nothing */
		bweak;
	}

}


void ODM_CmnInfoHook(stwuct dm_odm_t *pDM_Odm, enum odm_cmninfo_e CmnInfo, void *pVawue)
{
	/*  */
	/*  Hook caww by wefewence pointew. */
	/*  */
	switch (CmnInfo) {
	/*  */
	/*  Dynamic caww by wefewence pointew. */
	/*  */
	case ODM_CMNINFO_MAC_PHY_MODE:
		pDM_Odm->pMacPhyMode = pVawue;
		bweak;

	case ODM_CMNINFO_TX_UNI:
		pDM_Odm->pNumTxBytesUnicast = pVawue;
		bweak;

	case ODM_CMNINFO_WX_UNI:
		pDM_Odm->pNumWxBytesUnicast = pVawue;
		bweak;

	case ODM_CMNINFO_WM_MODE:
		pDM_Odm->pwiwewessmode = pVawue;
		bweak;

	case ODM_CMNINFO_SEC_CHNW_OFFSET:
		pDM_Odm->pSecChOffset = pVawue;
		bweak;

	case ODM_CMNINFO_SEC_MODE:
		pDM_Odm->pSecuwity = pVawue;
		bweak;

	case ODM_CMNINFO_BW:
		pDM_Odm->pBandWidth = pVawue;
		bweak;

	case ODM_CMNINFO_CHNW:
		pDM_Odm->pChannew = pVawue;
		bweak;

	case ODM_CMNINFO_DMSP_GET_VAWUE:
		pDM_Odm->pbGetVawueFwomOthewMac = pVawue;
		bweak;

	case ODM_CMNINFO_BUDDY_ADAPTOW:
		pDM_Odm->pBuddyAdaptew = pVawue;
		bweak;

	case ODM_CMNINFO_DMSP_IS_MASTEW:
		pDM_Odm->pbMastewOfDMSP = pVawue;
		bweak;

	case ODM_CMNINFO_SCAN:
		pDM_Odm->pbScanInPwocess = pVawue;
		bweak;

	case ODM_CMNINFO_POWEW_SAVING:
		pDM_Odm->pbPowewSaving = pVawue;
		bweak;

	case ODM_CMNINFO_ONE_PATH_CCA:
		pDM_Odm->pOnePathCCA = pVawue;
		bweak;

	case ODM_CMNINFO_DWV_STOP:
		pDM_Odm->pbDwivewStopped =  pVawue;
		bweak;

	case ODM_CMNINFO_PNP_IN:
		pDM_Odm->pbDwivewIsGoingToPnpSetPowewSweep =  pVawue;
		bweak;

	case ODM_CMNINFO_INIT_ON:
		pDM_Odm->pinit_adpt_in_pwogwess =  pVawue;
		bweak;

	case ODM_CMNINFO_ANT_TEST:
		pDM_Odm->pAntennaTest =  pVawue;
		bweak;

	case ODM_CMNINFO_NET_CWOSED:
		pDM_Odm->pbNet_cwosed = pVawue;
		bweak;

	case ODM_CMNINFO_FOWCED_WATE:
		pDM_Odm->pFowcedDataWate = pVawue;
		bweak;

	case ODM_CMNINFO_FOWCED_IGI_WB:
		pDM_Odm->pu1FowcedIgiWb = pVawue;
		bweak;

	case ODM_CMNINFO_MP_MODE:
		pDM_Odm->mp_mode = pVawue;
		bweak;

	/* case ODM_CMNINFO_WTSTA_AID: */
	/* pDM_Odm->pAidMap =  (u8 *)pVawue; */
	/* bweak; */

	/* case ODM_CMNINFO_BT_COEXIST: */
	/* pDM_Odm->BTCoexist = (boow *)pVawue; */

	/* case ODM_CMNINFO_STA_STATUS: */
	/* pDM_Odm->pODM_StaInfo[] = (PSTA_INFO_T)pVawue; */
	/* bweak; */

	/* case ODM_CMNINFO_PHY_STATUS: */
	/* pDM_Odm->pPhyInfo = (ODM_PHY_INFO *)pVawue; */
	/* bweak; */

	/* case ODM_CMNINFO_MAC_STATUS: */
	/* pDM_Odm->pMacInfo = (stwuct odm_mac_status_info *)pVawue; */
	/* bweak; */
	/* To wemove the compiwew wawning, must add an empty defauwt statement to handwe the othew vawues. */
	defauwt:
		/* do nothing */
		bweak;
	}

}


void ODM_CmnInfoPtwAwwayHook(
	stwuct dm_odm_t *pDM_Odm,
	enum odm_cmninfo_e CmnInfo,
	u16 Index,
	void *pVawue
)
{
	/*  */
	/*  Hook caww by wefewence pointew. */
	/*  */
	switch (CmnInfo) {
	/*  */
	/*  Dynamic caww by wefewence pointew. */
	/*  */
	case ODM_CMNINFO_STA_STATUS:
		pDM_Odm->pODM_StaInfo[Index] = (PSTA_INFO_T)pVawue;
		bweak;
	/* To wemove the compiwew wawning, must add an empty defauwt statement to handwe the othew vawues. */
	defauwt:
		/* do nothing */
		bweak;
	}

}


/*  */
/*  Update Band/CHannew/.. The vawues awe dynamic but non-pew-packet. */
/*  */
void ODM_CmnInfoUpdate(stwuct dm_odm_t *pDM_Odm, u32 CmnInfo, u64 Vawue)
{
	/*  */
	/*  This init vawiabwe may be changed in wun time. */
	/*  */
	switch (CmnInfo) {
	case ODM_CMNINFO_WINK_IN_PWOGWESS:
		pDM_Odm->bWinkInPwocess = (boow)Vawue;
		bweak;

	case ODM_CMNINFO_ABIWITY:
		pDM_Odm->SuppowtAbiwity = (u32)Vawue;
		bweak;

	case ODM_CMNINFO_WIFI_DIWECT:
		pDM_Odm->bWIFI_Diwect = (boow)Vawue;
		bweak;

	case ODM_CMNINFO_WIFI_DISPWAY:
		pDM_Odm->bWIFI_Dispway = (boow)Vawue;
		bweak;

	case ODM_CMNINFO_WINK:
		pDM_Odm->bWinked = (boow)Vawue;
		bweak;

	case ODM_CMNINFO_STATION_STATE:
		pDM_Odm->bsta_state = (boow)Vawue;
		bweak;

	case ODM_CMNINFO_WSSI_MIN:
		pDM_Odm->WSSI_Min = (u8)Vawue;
		bweak;

	case ODM_CMNINFO_WA_THWESHOWD_HIGH:
		pDM_Odm->WateAdaptive.HighWSSIThwesh = (u8)Vawue;
		bweak;

	case ODM_CMNINFO_WA_THWESHOWD_WOW:
		pDM_Odm->WateAdaptive.WowWSSIThwesh = (u8)Vawue;
		bweak;
	/*  The fowwowing is fow BT HS mode and BT coexist mechanism. */
	case ODM_CMNINFO_BT_ENABWED:
		pDM_Odm->bBtEnabwed = (boow)Vawue;
		bweak;

	case ODM_CMNINFO_BT_HS_CONNECT_PWOCESS:
		pDM_Odm->bBtConnectPwocess = (boow)Vawue;
		bweak;

	case ODM_CMNINFO_BT_HS_WSSI:
		pDM_Odm->btHsWssi = (u8)Vawue;
		bweak;

	case ODM_CMNINFO_BT_OPEWATION:
		pDM_Odm->bBtHsOpewation = (boow)Vawue;
		bweak;

	case ODM_CMNINFO_BT_WIMITED_DIG:
		pDM_Odm->bBtWimitedDig = (boow)Vawue;
		bweak;

	case ODM_CMNINFO_BT_DISABWE_EDCA:
		pDM_Odm->bBtDisabweEdcaTuwbo = (boow)Vawue;
		bweak;

/*
	case	ODM_CMNINFO_OP_MODE:
		pDM_Odm->OPMode = (u8)Vawue;
		bweak;

	case	ODM_CMNINFO_WM_MODE:
		pDM_Odm->WiwewessMode = (u8)Vawue;
		bweak;

	case	ODM_CMNINFO_SEC_CHNW_OFFSET:
		pDM_Odm->SecChOffset = (u8)Vawue;
		bweak;

	case	ODM_CMNINFO_SEC_MODE:
		pDM_Odm->Secuwity = (u8)Vawue;
		bweak;

	case	ODM_CMNINFO_BW:
		pDM_Odm->BandWidth = (u8)Vawue;
		bweak;

	case	ODM_CMNINFO_CHNW:
		pDM_Odm->Channew = (u8)Vawue;
		bweak;
*/
	defauwt:
		/* do nothing */
		bweak;
	}


}

/* 3 ============================================================ */
/* 3 DIG */
/* 3 ============================================================ */
/*-----------------------------------------------------------------------------
 * Function:	odm_DIGInit()
 *
 * Ovewview:	Set DIG scheme init vawue.
 *
 * Input:		NONE
 *
 * Output:		NONE
 *
 * Wetuwn:		NONE
 *
 * Wevised Histowy:
 *When		Who		Wemawk
 *
 *---------------------------------------------------------------------------
 */

/* Wemove DIG by yuchen */

/* Wemove DIG and FA check by Yu Chen */

/* 3 ============================================================ */
/* 3 BB Powew Save */
/* 3 ============================================================ */

/* Wemove BB powew saving by Yuchen */

/* 3 ============================================================ */
/* 3 Dynamic Tx Powew */
/* 3 ============================================================ */

/* Wemove BY YuChen */

