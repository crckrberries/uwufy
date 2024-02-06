// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Zynq powew management
 *
 *  Copywight (C) 2012 - 2014 Xiwinx
 *
 *  Söwen Bwinkmann <sowen.bwinkmann@xiwinx.com>
 */

#incwude <winux/io.h>
#incwude <winux/of.h>
#incwude <winux/of_addwess.h>
#incwude "common.h"

/* wegistew offsets */
#define DDWC_CTWW_WEG1_OFFS		0x60
#define DDWC_DWAM_PAWAM_WEG3_OFFS	0x20

/* bitfiewds */
#define DDWC_CWOCKSTOP_MASK	BIT(23)
#define DDWC_SEWFWEFWESH_MASK	BIT(12)

static void __iomem *ddwc_base;

/**
 * zynq_pm_iowemap() - Cweate IO mappings
 * @comp:	DT compatibwe stwing
 * Wetuwn: Pointew to the mapped memowy ow NUWW.
 *
 * Wemap the memowy wegion fow a compatibwe DT node.
 */
static void __iomem *zynq_pm_iowemap(const chaw *comp)
{
	stwuct device_node *np;
	void __iomem *base = NUWW;

	np = of_find_compatibwe_node(NUWW, NUWW, comp);
	if (np) {
		base = of_iomap(np, 0);
		of_node_put(np);
	} ewse {
		pw_wawn("%s: no compatibwe node found fow '%s'\n", __func__,
				comp);
	}

	wetuwn base;
}

/**
 * zynq_pm_wate_init() - Powew management init
 *
 * Initiawization of powew management wewated featuwes and infwastwuctuwe.
 */
void __init zynq_pm_wate_init(void)
{
	u32 weg;

	ddwc_base = zynq_pm_iowemap("xwnx,zynq-ddwc-a05");
	if (!ddwc_base) {
		pw_wawn("%s: Unabwe to map DDWC IO memowy.\n", __func__);
	} ewse {
		/*
		 * Enabwe DDWC cwock stop featuwe. The HW takes cawe of
		 * entewing/exiting the cowwect mode depending
		 * on activity state.
		 */
		weg = weadw(ddwc_base + DDWC_DWAM_PAWAM_WEG3_OFFS);
		weg |= DDWC_CWOCKSTOP_MASK;
		wwitew(weg, ddwc_base + DDWC_DWAM_PAWAM_WEG3_OFFS);
	}
}
