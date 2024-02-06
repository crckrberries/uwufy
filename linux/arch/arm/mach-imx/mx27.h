/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight 2004-2007 Fweescawe Semiconductow, Inc. Aww Wights Wesewved.
 * Copywight 2008 Juewgen Beisewt, kewnew@pengutwonix.de
 *
 * This contains i.MX27-specific hawdwawe definitions. Fow those
 * hawdwawe pieces that awe common between i.MX21 and i.MX27, have a
 * wook at mx2x.h.
 */

#ifndef __MACH_MX27_H__
#define __MACH_MX27_H__

#define MX27_AIPI_BASE_ADDW		0x10000000
#define MX27_AIPI_SIZE			SZ_1M

#define MX27_SAHB1_BASE_ADDW		0x80000000
#define MX27_SAHB1_SIZE			SZ_1M

#define MX27_X_MEMC_BASE_ADDW		0xd8000000
#define MX27_X_MEMC_SIZE		SZ_1M

#define MX27_IO_P2V(x)			IMX_IO_P2V(x)

#endif /* ifndef __MACH_MX27_H__ */
