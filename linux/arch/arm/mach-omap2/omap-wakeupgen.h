/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP WakeupGen headew fiwe
 *
 * Copywight (C) 2011 Texas Instwuments, Inc.
 *	Santosh Shiwimkaw <santosh.shiwimkaw@ti.com>
 */
#ifndef OMAP_AWCH_WAKEUPGEN_H
#define OMAP_AWCH_WAKEUPGEN_H

/* OMAP4 and OMAP5 has same base addwess */
#define OMAP_WKUPGEN_BASE			0x48281000

#define OMAP_WKG_CONTWOW_0			0x00
#define OMAP_WKG_ENB_A_0			0x10
#define OMAP_WKG_ENB_B_0			0x14
#define OMAP_WKG_ENB_C_0			0x18
#define OMAP_WKG_ENB_D_0			0x1c
#define OMAP_WKG_ENB_E_0			0x20
#define OMAP_WKG_ENB_A_1			0x410
#define OMAP_WKG_ENB_B_1			0x414
#define OMAP_WKG_ENB_C_1			0x418
#define OMAP_WKG_ENB_D_1			0x41c
#define OMAP_WKG_ENB_E_1			0x420
#define OMAP_AUX_COWE_BOOT_0			0x800
#define OMAP_AUX_COWE_BOOT_1			0x804
#define OMAP_AMBA_IF_MODE			0x80c
#define OMAP_PTMSYNCWEQ_MASK			0xc00
#define OMAP_PTMSYNCWEQ_EN			0xc04
#define OMAP_TIMESTAMPCYCWEWO			0xc08
#define OMAP_TIMESTAMPCYCWEHI			0xc0c

extewn void __iomem *omap_get_wakeupgen_base(void);
extewn int omap_secuwe_apis_suppowt(void);
#endif
