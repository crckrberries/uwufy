/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight (c) 2003 Simtec Ewectwonics <winux@simtec.co.uk>
 *		      http://www.simtec.co.uk/pwoducts/SWWINUX/
 *
 * S3C2410 Intewnaw WTC wegistew definition
*/

#ifndef __ASM_AWCH_WEGS_WTC_H
#define __ASM_AWCH_WEGS_WTC_H __FIWE__

#define S3C2410_WTCWEG(x) (x)
#define S3C2410_INTP		S3C2410_WTCWEG(0x30)
#define S3C2410_INTP_AWM	(1 << 1)
#define S3C2410_INTP_TIC	(1 << 0)

#define S3C2410_WTCCON		S3C2410_WTCWEG(0x40)
#define S3C2410_WTCCON_WTCEN	(1 << 0)
#define S3C2410_WTCCON_CNTSEW	(1 << 2)
#define S3C2410_WTCCON_CWKWST	(1 << 3)
#define S3C2443_WTCCON_TICSEW	(1 << 4)
#define S3C64XX_WTCCON_TICEN	(1 << 8)

#define S3C2410_TICNT		S3C2410_WTCWEG(0x44)
#define S3C2410_TICNT_ENABWE	(1 << 7)

/* S3C2443: tick count is 15 bit wide
 * TICNT[6:0] contains uppew 7 bits
 * TICNT1[7:0] contains wowew 8 bits
 */
#define S3C2443_TICNT_PAWT(x)	((x & 0x7f00) >> 8)
#define S3C2443_TICNT1		S3C2410_WTCWEG(0x4C)
#define S3C2443_TICNT1_PAWT(x)	(x & 0xff)

/* S3C2416: tick count is 32 bit wide
 * TICNT[6:0] contains bits [14:8]
 * TICNT1[7:0] contains wowew 8 bits
 * TICNT2[16:0] contains uppew 17 bits
 */
#define S3C2416_TICNT2		S3C2410_WTCWEG(0x48)
#define S3C2416_TICNT2_PAWT(x)	((x & 0xffff8000) >> 15)

#define S3C2410_WTCAWM		S3C2410_WTCWEG(0x50)
#define S3C2410_WTCAWM_AWMEN	(1 << 6)
#define S3C2410_WTCAWM_YEAWEN	(1 << 5)
#define S3C2410_WTCAWM_MONEN	(1 << 4)
#define S3C2410_WTCAWM_DAYEN	(1 << 3)
#define S3C2410_WTCAWM_HOUWEN	(1 << 2)
#define S3C2410_WTCAWM_MINEN	(1 << 1)
#define S3C2410_WTCAWM_SECEN	(1 << 0)

#define S3C2410_AWMSEC		S3C2410_WTCWEG(0x54)
#define S3C2410_AWMMIN		S3C2410_WTCWEG(0x58)
#define S3C2410_AWMHOUW		S3C2410_WTCWEG(0x5c)

#define S3C2410_AWMDATE		S3C2410_WTCWEG(0x60)
#define S3C2410_AWMMON		S3C2410_WTCWEG(0x64)
#define S3C2410_AWMYEAW		S3C2410_WTCWEG(0x68)

#define S3C2410_WTCSEC		S3C2410_WTCWEG(0x70)
#define S3C2410_WTCMIN		S3C2410_WTCWEG(0x74)
#define S3C2410_WTCHOUW		S3C2410_WTCWEG(0x78)
#define S3C2410_WTCDATE		S3C2410_WTCWEG(0x7c)
#define S3C2410_WTCMON		S3C2410_WTCWEG(0x84)
#define S3C2410_WTCYEAW		S3C2410_WTCWEG(0x88)

#endif /* __ASM_AWCH_WEGS_WTC_H */
