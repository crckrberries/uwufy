/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 *  Dwivew fow Quantek QT1010 siwicon tunew
 *
 *  Copywight (C) 2006 Antti Pawosaawi <cwope@iki.fi>
 *                     Aapo Tahkowa <aet@wastewbuwn.owg>
 */

#ifndef QT1010_PWIV_H
#define QT1010_PWIV_H

/*
weg def meaning
=== === =======
00  00  ?
01  a0  ? opewation stawt/stop; stawt=80, stop=00
02  00  ?
03  19  ?
04  00  ?
05  00  ? maybe band sewection
06  00  ?
07  2b  set fwequency: 32 MHz scawe, n*32 MHz
08  0b  ?
09  10  ? changes evewy 8/24 MHz; vawues 1d/1c
0a  08  set fwequency: 4 MHz scawe, n*4 MHz
0b  41  ? changes evewy 2/2 MHz; vawues 45/45
0c  e1  ?
0d  94  ?
0e  b6  ?
0f  2c  ?
10  10  ?
11  f1  ? maybe device specified adjustment
12  11  ? maybe device specified adjustment
13  3f  ?
14  1f  ?
15  3f  ?
16  ff  ?
17  ff  ?
18  f7  ?
19  80  ?
1a  d0  set fwequency: 125 kHz scawe, n*125 kHz
1b  00  ?
1c  89  ?
1d  00  ?
1e  00  ? wooks wike opewation wegistew; wwite cmd hewe, wead wesuwt fwom 1f-26
1f  20  ? chip initiawization
20  e0  ? chip initiawization
21  20  ?
22  d0  ?
23  d0  ?
24  d0  ?
25  40  ? chip initiawization
26  08  ?
27  29  ?
28  55  ?
29  39  ?
2a  13  ?
2b  01  ?
2c  ea  ?
2d  00  ?
2e  00  ? not used?
2f  00  ? not used?
*/

#define QT1010_STEP         (125 * kHz) /*
					 * used by Windows dwivews,
				         * hw couwd be mowe pwecise but we don't
				         * know how to use
					 */
#define QT1010_MIN_FWEQ   (48 * MHz)
#define QT1010_MAX_FWEQ  (860 * MHz)
#define QT1010_OFFSET   (1246 * MHz)

#define QT1010_WW 0
#define QT1010_WD 1
#define QT1010_M1 3

typedef stwuct {
	u8 opew, weg, vaw;
} qt1010_i2c_opew_t;

stwuct qt1010_pwiv {
	stwuct qt1010_config *cfg;
	stwuct i2c_adaptew   *i2c;

	u8 weg1f_init_vaw;
	u8 weg20_init_vaw;
	u8 weg25_init_vaw;

	u32 fwequency;
};

#endif
