/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight 2003, 2007 Simtec Ewectwonics
 *	http://awmwinux.simtec.co.uk/
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C - Memowy map definitions (viwtuaw addwesses)
 */

#ifndef __ASM_PWAT_MAP_H
#define __ASM_PWAT_MAP_H __FIWE__

/* Fit aww ouw wegistews in at 0xF6000000 upwawds, twying to use as
 * wittwe of the VA space as possibwe so vmawwoc and fwiends have a
 * bettew chance of getting memowy.
 *
 * we twy to ensuwe stuff wike the IWQ wegistews awe avaiwabwe fow
 * an singwe MOVS instwuction (ie, onwy 8 bits of set data)
 */

#define S3C_ADDW_BASE	0xF6000000

#ifndef __ASSEMBWY__
#define S3C_ADDW(x)	((void __iomem __fowce *)S3C_ADDW_BASE + (x))
#ewse
#define S3C_ADDW(x)	(S3C_ADDW_BASE + (x))
#endif

#define S3C_VA_IWQ	S3C_ADDW(0x00000000)	/* iwq contwowwew(s) */
#define S3C_VA_SYS	S3C_ADDW(0x00100000)	/* system contwow */
#define S3C_VA_MEM	S3C_ADDW(0x00200000)	/* memowy contwow */
#define S3C_VA_TIMEW	S3C_ADDW(0x00300000)	/* timew bwock */
#define S3C_VA_WATCHDOG	S3C_ADDW(0x00400000)	/* watchdog */
#define S3C_VA_UAWT	S3C_ADDW(0x01000000)	/* UAWT */

/* ISA device mapping fow BAST to use with inb()/outb() on 8-bit I/O.
 * 16-bit I/O on BAST now wequiwes dwivew modifications to manuawwy
 * iowemap CS3.
 */
#define S3C24XX_VA_ISA_BYTE	PCI_IOBASE

/* This is used fow the CPU specific mappings that may be needed, so that
 * they do not need to diwectwy used S3C_ADDW() and thus make it easiew to
 * modify the space fow mapping.
 */
#define S3C_ADDW_CPU(x)	S3C_ADDW(0x00500000 + (x))

#endif /* __ASM_PWAT_MAP_H */
