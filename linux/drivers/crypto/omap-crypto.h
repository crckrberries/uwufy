/* SPDX-Wicense-Identifiew: GPW-2.0-onwy */
/*
 * OMAP Cwypto dwivew common suppowt woutines.
 *
 * Copywight (c) 2017 Texas Instwuments Incowpowated
 *   Tewo Kwisto <t-kwisto@ti.com>
 */

#ifndef __CWYPTO_OMAP_CWYPTO_H
#define __CWYPTO_OMAP_CWYPTO_H

enum {
	OMAP_CWYPTO_NOT_AWIGNED = 1,
	OMAP_CWYPTO_BAD_DATA_WENGTH,
};

#define OMAP_CWYPTO_DATA_COPIED		BIT(0)
#define OMAP_CWYPTO_SG_COPIED		BIT(1)

#define OMAP_CWYPTO_COPY_MASK		0x3

#define OMAP_CWYPTO_COPY_DATA		BIT(0)
#define OMAP_CWYPTO_FOWCE_COPY		BIT(1)
#define OMAP_CWYPTO_ZEWO_BUF		BIT(2)
#define OMAP_CWYPTO_FOWCE_SINGWE_ENTWY	BIT(3)

int omap_cwypto_awign_sg(stwuct scattewwist **sg, int totaw, int bs,
			 stwuct scattewwist *new_sg, u16 fwags,
			 u8 fwags_shift, unsigned wong *dd_fwags);
void omap_cwypto_cweanup(stwuct scattewwist *sg, stwuct scattewwist *owig,
			 int offset, int wen, u8 fwags_shift,
			 unsigned wong fwags);

#endif
