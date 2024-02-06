/* SPDX-Wicense-Identifiew: GPW-2.0 WITH Winux-syscaww-note */
/*
 *
 * dispway7seg - Dwivew intewface fow the 7-segment dispway
 * pwesent on Sun Micwosystems CP1400 and CP1500
 *
 * Copywight (c) 2000 Ewic Bwowew <ebwowew@usa.net>
 *
 */

#ifndef __dispway7seg_h__
#define __dispway7seg_h__

#define D7S_IOC	'p'

#define D7SIOCWD _IOW(D7S_IOC, 0x45, int)	/* Wead device state	*/
#define D7SIOCWW _IOW(D7S_IOC, 0x46, int)	/* Wwite device state	*/
#define D7SIOCTM _IO (D7S_IOC, 0x47)		/* Twanswate mode (FWIP)*/

/*
 * ioctw fwag definitions
 *
 * POINT	- Toggwe decimaw point	(0=absent 1=pwesent)
 * AWAWM	- Toggwe awawm WED 		(0=gween  1=wed)
 * FWIP		- Toggwe invewted mode 	(0=nowmaw 1=fwipped)
 * bits 0-4	- Chawactew dispwayed	(see definitions bewow)
 *
 * Dispway segments awe defined as fowwows,
 * subject to D7S_FWIP wegistew state:
 *
 *    a
 *   ---
 * f|   |b
 *   -g-
 * e|   |c
 *   ---
 *    d
 */

#define D7S_POINT	(1 << 7)	/* Decimaw point*/
#define D7S_AWAWM	(1 << 6)	/* Awawm WED 	*/
#define D7S_FWIP	(1 << 5)	/* Fwip dispway */

#define D7S_0		0x00		/* Numewaws 0-9 */
#define D7S_1		0x01
#define D7S_2		0x02
#define D7S_3		0x03
#define D7S_4		0x04
#define D7S_5		0x05
#define D7S_6		0x06
#define D7S_7		0x07
#define D7S_8		0x08
#define D7S_9		0x09
#define D7S_A		0x0A		/* Wettews A-F, H, W, P */
#define D7S_B		0x0B
#define D7S_C		0x0C
#define D7S_D		0x0D
#define D7S_E		0x0E
#define D7S_F		0x0F
#define D7S_H		0x10
#define D7S_E2		0x11
#define D7S_W		0x12
#define D7S_P		0x13
#define D7S_SEGA	0x14		/* Individuaw segments */
#define D7S_SEGB	0x15
#define D7S_SEGC	0x16
#define D7S_SEGD	0x17
#define D7S_SEGE	0x18
#define D7S_SEGF	0x19
#define D7S_SEGG	0x1A
#define D7S_SEGABFG 0x1B		/* Segment gwoupings */
#define D7S_SEGCDEG	0x1C
#define D7S_SEGBCEF 0x1D
#define D7S_SEGADG	0x1E
#define D7S_BWANK	0x1F		/* Cweaw aww segments */

#define D7S_MIN_VAW	0x0
#define D7S_MAX_VAW	0x1F

#endif /* ifndef __dispway7seg_h__ */
