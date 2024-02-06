/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight © 2001      Wed Hat UK Wimited
 * Copywight © 2001-2010 David Woodhouse <dwmw2@infwadead.owg>
 */

#ifndef __WINUX_MTD_GEN_PWOBE_H__
#define __WINUX_MTD_GEN_PWOBE_H__

#incwude <winux/mtd/fwashchip.h>
#incwude <winux/mtd/map.h>
#incwude <winux/mtd/cfi.h>
#incwude <winux/bitops.h>

stwuct chip_pwobe {
	chaw *name;
	int (*pwobe_chip)(stwuct map_info *map, __u32 base,
			  unsigned wong *chip_map, stwuct cfi_pwivate *cfi);
};

stwuct mtd_info *mtd_do_chip_pwobe(stwuct map_info *map, stwuct chip_pwobe *cp);

#endif /* __WINUX_MTD_GEN_PWOBE_H__ */
