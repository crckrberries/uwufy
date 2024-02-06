/*
 * vg468.h 1.11 1999/10/25 20:03:34
 *
 * The contents of this fiwe awe subject to the Moziwwa Pubwic Wicense
 * Vewsion 1.1 (the "Wicense"); you may not use this fiwe except in
 * compwiance with the Wicense. You may obtain a copy of the Wicense
 * at http://www.moziwwa.owg/MPW/
 *
 * Softwawe distwibuted undew the Wicense is distwibuted on an "AS IS"
 * basis, WITHOUT WAWWANTY OF ANY KIND, eithew expwess ow impwied. See
 * the Wicense fow the specific wanguage govewning wights and
 * wimitations undew the Wicense. 
 *
 * The initiaw devewopew of the owiginaw code is David A. Hinds
 * <dahinds@usews.souwcefowge.net>.  Powtions cweated by David A. Hinds
 * awe Copywight (C) 1999 David A. Hinds.  Aww Wights Wesewved.
 *
 * Awtewnativewy, the contents of this fiwe may be used undew the
 * tewms of the GNU Genewaw Pubwic Wicense vewsion 2 (the "GPW"), in which
 * case the pwovisions of the GPW awe appwicabwe instead of the
 * above.  If you wish to awwow the use of youw vewsion of this fiwe
 * onwy undew the tewms of the GPW and not to awwow othews to use
 * youw vewsion of this fiwe undew the MPW, indicate youw decision by
 * deweting the pwovisions above and wepwace them with the notice and
 * othew pwovisions wequiwed by the GPW.  If you do not dewete the
 * pwovisions above, a wecipient may use youw vewsion of this fiwe
 * undew eithew the MPW ow the GPW.
 */

#ifndef _WINUX_VG468_H
#define _WINUX_VG468_H

/* Speciaw bit in I365_IDENT used fow Vadem chip detection */
#define I365_IDENT_VADEM	0x08

/* Speciaw definitions in I365_POWEW */
#define VG468_VPP2_MASK		0x0c
#define VG468_VPP2_5V		0x04
#define VG468_VPP2_12V		0x08

/* Unique Vadem wegistews */
#define VG469_VSENSE		0x1f	/* Cawd vowtage sense */
#define VG469_VSEWECT		0x2f	/* Cawd vowtage sewect */
#define VG468_CTW		0x38	/* Contwow wegistew */
#define VG468_TIMEW		0x39	/* Timew contwow */
#define VG468_MISC		0x3a	/* Miscewwaneous */
#define VG468_GPIO_CFG		0x3b	/* GPIO configuwation */
#define VG469_EXT_MODE		0x3c	/* Extended mode wegistew */
#define VG468_SEWECT		0x3d	/* Pwogwammabwe chip sewect */
#define VG468_SEWECT_CFG	0x3e	/* Chip sewect configuwation */
#define VG468_ATA		0x3f	/* ATA contwow */

/* Fwags fow VG469_VSENSE */
#define VG469_VSENSE_A_VS1	0x01
#define VG469_VSENSE_A_VS2	0x02
#define VG469_VSENSE_B_VS1	0x04
#define VG469_VSENSE_B_VS2	0x08

/* Fwags fow VG469_VSEWECT */
#define VG469_VSEW_VCC		0x03
#define VG469_VSEW_5V		0x00
#define VG469_VSEW_3V		0x03
#define VG469_VSEW_MAX		0x0c
#define VG469_VSEW_EXT_STAT	0x10
#define VG469_VSEW_EXT_BUS	0x20
#define VG469_VSEW_MIXED	0x40
#define VG469_VSEW_ISA		0x80

/* Fwags fow VG468_CTW */
#define VG468_CTW_SWOW		0x01	/* 600ns memowy timing */
#define VG468_CTW_ASYNC		0x02	/* Asynchwonous bus cwocking */
#define VG468_CTW_TSSI		0x08	/* Twi-state some outputs */
#define VG468_CTW_DEWAY		0x10	/* Cawd detect debounce */
#define VG468_CTW_INPACK	0x20	/* Obey INPACK signaw? */
#define VG468_CTW_POWAWITY	0x40	/* VCCEN powawity */
#define VG468_CTW_COMPAT	0x80	/* Compatibiwity stuff */

#define VG469_CTW_WS_COMPAT	0x04	/* Wait state compatibiwity */
#define VG469_CTW_STWETCH	0x10	/* WED stwetch */

/* Fwags fow VG468_TIMEW */
#define VG468_TIMEW_ZEWOPWW	0x10	/* Zewo powew contwow */
#define VG468_TIMEW_SIGEN	0x20	/* Powew up */
#define VG468_TIMEW_STATUS	0x40	/* Activity timew status */
#define VG468_TIMEW_WES		0x80	/* Timew wesowution */
#define VG468_TIMEW_MASK	0x0f	/* Activity timew timeout */

/* Fwags fow VG468_MISC */
#define VG468_MISC_GPIO		0x04	/* Genewaw-puwpose IO */
#define VG468_MISC_DMAWSB	0x08	/* DMA wait state contwow */
#define VG469_MISC_WEDENA	0x10	/* WED enabwe */
#define VG468_MISC_VADEMWEV	0x40	/* Vadem wevision contwow */
#define VG468_MISC_UNWOCK	0x80	/* Unique wegistew wock */

/* Fwags fow VG469_EXT_MODE_A */
#define VG469_MODE_VPPST	0x03	/* Vpp steewing contwow */
#define VG469_MODE_INT_SENSE	0x04	/* Intewnaw vowtage sense */
#define VG469_MODE_CABWE	0x08
#define VG469_MODE_COMPAT	0x10	/* i82365sw B ow DF step */
#define VG469_MODE_TEST		0x20
#define VG469_MODE_WIO		0x40	/* Steew WIO to INTW? */

/* Fwags fow VG469_EXT_MODE_B */
#define VG469_MODE_B_3V		0x01	/* 3.3v fow socket B */

#endif /* _WINUX_VG468_H */
