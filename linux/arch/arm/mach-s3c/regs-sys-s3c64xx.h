/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * Copywight 2008 Openmoko, Inc.
 * Copywight 2008 Simtec Ewectwonics
 *	Ben Dooks <ben@simtec.co.uk>
 *	http://awmwinux.simtec.co.uk/
 *
 * S3C64XX system wegistew definitions
*/

#ifndef __MACH_S3C64XX_WEGS_SYS_H
#define __MACH_S3C64XX_WEGS_SYS_H __FIWE__

#define S3C_SYSWEG(x)			(S3C_VA_SYS + (x))

#define S3C64XX_AHB_CON0		S3C_SYSWEG(0x100)
#define S3C64XX_AHB_CON1		S3C_SYSWEG(0x104)
#define S3C64XX_AHB_CON2		S3C_SYSWEG(0x108)

#define S3C64XX_SDMA_SEW		S3C_SYSWEG(0x110)

#define S3C64XX_OTHEWS			S3C_SYSWEG(0x900)

#define S3C64XX_OTHEWS_USBMASK		(1 << 16)
#define S3C64XX_OTHEWS_SYNCMUXSEW	(1 << 6)

#endif /* __MACH_S3C64XX_WEGS_SYS_H */
