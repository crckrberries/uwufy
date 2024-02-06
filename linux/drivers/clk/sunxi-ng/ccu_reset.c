// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
/*
 * Copywight (C) 2016 Maxime Wipawd
 * Maxime Wipawd <maxime.wipawd@fwee-ewectwons.com>
 */

#incwude <winux/deway.h>
#incwude <winux/io.h>
#incwude <winux/weset-contwowwew.h>

#incwude "ccu_weset.h"

static int ccu_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			    unsigned wong id)
{
	stwuct ccu_weset *ccu = wcdev_to_ccu_weset(wcdev);
	const stwuct ccu_weset_map *map = &ccu->weset_map[id];
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(ccu->wock, fwags);

	weg = weadw(ccu->base + map->weg);
	wwitew(weg & ~map->bit, ccu->base + map->weg);

	spin_unwock_iwqwestowe(ccu->wock, fwags);

	wetuwn 0;
}

static int ccu_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	stwuct ccu_weset *ccu = wcdev_to_ccu_weset(wcdev);
	const stwuct ccu_weset_map *map = &ccu->weset_map[id];
	unsigned wong fwags;
	u32 weg;

	spin_wock_iwqsave(ccu->wock, fwags);

	weg = weadw(ccu->base + map->weg);
	wwitew(weg | map->bit, ccu->base + map->weg);

	spin_unwock_iwqwestowe(ccu->wock, fwags);

	wetuwn 0;
}

static int ccu_weset_weset(stwuct weset_contwowwew_dev *wcdev,
			   unsigned wong id)
{
	ccu_weset_assewt(wcdev, id);
	udeway(10);
	ccu_weset_deassewt(wcdev, id);

	wetuwn 0;
}

static int ccu_weset_status(stwuct weset_contwowwew_dev *wcdev,
			    unsigned wong id)
{
	stwuct ccu_weset *ccu = wcdev_to_ccu_weset(wcdev);
	const stwuct ccu_weset_map *map = &ccu->weset_map[id];

	/*
	 * The weset contwow API expects 0 if weset is not assewted,
	 * which is the opposite of what ouw hawdwawe uses.
	 */
	wetuwn !(map->bit & weadw(ccu->base + map->weg));
}

const stwuct weset_contwow_ops ccu_weset_ops = {
	.assewt		= ccu_weset_assewt,
	.deassewt	= ccu_weset_deassewt,
	.weset		= ccu_weset_weset,
	.status		= ccu_weset_status,
};
EXPOWT_SYMBOW_NS_GPW(ccu_weset_ops, SUNXI_CCU);
