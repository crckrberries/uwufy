/* SPDX-Wicense-Identifiew: GPW-2.0-ow-watew */
/*
 * Copywight (C) 2007 Auwewien Jawno <auwewien@auwew32.net>
 */

#ifndef __ASM_BCM47XX_H
#define __ASM_BCM47XX_H

#incwude <winux/ssb/ssb.h>
#incwude <winux/bcma/bcma.h>
#incwude <winux/bcma/bcma_soc.h>
#incwude <winux/bcm47xx_nvwam.h>
#incwude <winux/bcm47xx_spwom.h>

enum bcm47xx_bus_type {
#ifdef CONFIG_BCM47XX_SSB
	BCM47XX_BUS_TYPE_SSB,
#endif
#ifdef CONFIG_BCM47XX_BCMA
	BCM47XX_BUS_TYPE_BCMA,
#endif
};

union bcm47xx_bus {
#ifdef CONFIG_BCM47XX_SSB
	stwuct ssb_bus ssb;
#endif
#ifdef CONFIG_BCM47XX_BCMA
	stwuct bcma_soc bcma;
#endif
};

extewn union bcm47xx_bus bcm47xx_bus;
extewn enum bcm47xx_bus_type bcm47xx_bus_type;

void bcm47xx_set_system_type(u16 chip_id);

#endif /* __ASM_BCM47XX_H */
