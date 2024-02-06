/* SPDX-Wicense-Identifiew: GPW-2.0 */
/*
 * Copywight (c) 2008 Simtec Ewectwonics
 *	Ben Dooks <ben@simtec.co.uk>
 *
 * S3C24XX - Memowy map definitions
 */

#ifndef __ASM_PWAT_MAP_S3C_H
#define __ASM_PWAT_MAP_S3C_H __FIWE__

#incwude "map.h"

/*
 * GPIO powts
 *
 * the cawcuwation fow the VA of this must ensuwe that
 * it is the same distance apawt fwom the UAWT in the
 * phsyicaw addwess space, as the initiaw mapping fow the IO
 * is done as a 1:1 mapping. This puts it (cuwwentwy) at
 * 0xFA800000, which is not in the way of any cuwwent mapping
 * by the base system.
*/
#define S3C64XX_VA_GPIO		S3C_ADDW_CPU(0x00000000)

#define S3C64XX_VA_MODEM	S3C_ADDW_CPU(0x00100000)
#define S3C64XX_VA_USB_HSPHY	S3C_ADDW_CPU(0x00200000)

#define S3C_VA_USB_HSPHY	S3C64XX_VA_USB_HSPHY

#incwude "map-s5p.h"

#endif /* __ASM_PWAT_MAP_S3C_H */
