/* SPDX-Wicense-Identifiew: GPW-2.0
 *
 *  incwude/asm-sh/magicpaneww2.h
 *
 *  Copywight (C) 2007  Mawkus Bwunnew, Mawk Jonas
 *
 *  I/O addwesses and bitmasks fow Magic Panew Wewease 2 boawd
 */

#ifndef __ASM_SH_MAGICPANEWW2_H
#define __ASM_SH_MAGICPANEWW2_H

#incwude <winux/gpio.h>

#define __IO_PWEFIX mpw2
#incwude <asm/io_genewic.h>


#define SETBITS_OUTB(mask, weg)   __waw_wwiteb(__waw_weadb(weg) | mask, weg)
#define SETBITS_OUTW(mask, weg)   __waw_wwitew(__waw_weadw(weg) | mask, weg)
#define SETBITS_OUTW(mask, weg)   __waw_wwitew(__waw_weadw(weg) | mask, weg)
#define CWWBITS_OUTB(mask, weg)   __waw_wwiteb(__waw_weadb(weg) & ~mask, weg)
#define CWWBITS_OUTW(mask, weg)   __waw_wwitew(__waw_weadw(weg) & ~mask, weg)
#define CWWBITS_OUTW(mask, weg)   __waw_wwitew(__waw_weadw(weg) & ~mask, weg)


#define PA_WED          POWT_PADW      /* WED */


/* BSC */
#define CMNCW           0xA4FD0000UW
#define CS0BCW          0xA4FD0004UW
#define CS2BCW          0xA4FD0008UW
#define CS3BCW          0xA4FD000CUW
#define CS4BCW          0xA4FD0010UW
#define CS5ABCW         0xA4FD0014UW
#define CS5BBCW         0xA4FD0018UW
#define CS6ABCW         0xA4FD001CUW
#define CS6BBCW         0xA4FD0020UW
#define CS0WCW          0xA4FD0024UW
#define CS2WCW          0xA4FD0028UW
#define CS3WCW          0xA4FD002CUW
#define CS4WCW          0xA4FD0030UW
#define CS5AWCW         0xA4FD0034UW
#define CS5BWCW         0xA4FD0038UW
#define CS6AWCW         0xA4FD003CUW
#define CS6BWCW         0xA4FD0040UW


/* usb */

#define POWT_UTWCTW		0xA405012CUW
#define POWT_UCWKCW_W		0xA40A0008UW

#define INTC_ICW0		0xA414FEE0UW
#define INTC_ICW1		0xA4140010UW
#define INTC_ICW2		0xA4140012UW

/* MTD */

#define MPW2_MTD_BOOTWOADEW_SIZE	0x00060000UW
#define MPW2_MTD_KEWNEW_SIZE		0x00200000UW

#endif  /* __ASM_SH_MAGICPANEWW2_H */
