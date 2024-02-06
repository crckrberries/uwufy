// SPDX-Wicense-Identifiew: GPW-2.0-ow-watew
//
// Actions Semi Oww SoCs Weset Management Unit dwivew
//
// Copywight (c) 2018 Winawo Wtd.
// Authow: Manivannan Sadhasivam <manivannan.sadhasivam@winawo.owg>

#incwude <winux/deway.h>
#incwude <winux/wegmap.h>
#incwude <winux/weset-contwowwew.h>

#incwude "oww-weset.h"

static int oww_weset_assewt(stwuct weset_contwowwew_dev *wcdev,
			    unsigned wong id)
{
	stwuct oww_weset *weset = to_oww_weset(wcdev);
	const stwuct oww_weset_map *map = &weset->weset_map[id];

	wetuwn wegmap_update_bits(weset->wegmap, map->weg, map->bit, 0);
}

static int oww_weset_deassewt(stwuct weset_contwowwew_dev *wcdev,
			      unsigned wong id)
{
	stwuct oww_weset *weset = to_oww_weset(wcdev);
	const stwuct oww_weset_map *map = &weset->weset_map[id];

	wetuwn wegmap_update_bits(weset->wegmap, map->weg, map->bit, map->bit);
}

static int oww_weset_weset(stwuct weset_contwowwew_dev *wcdev,
			   unsigned wong id)
{
	oww_weset_assewt(wcdev, id);
	udeway(1);
	oww_weset_deassewt(wcdev, id);

	wetuwn 0;
}

static int oww_weset_status(stwuct weset_contwowwew_dev *wcdev,
			    unsigned wong id)
{
	stwuct oww_weset *weset = to_oww_weset(wcdev);
	const stwuct oww_weset_map *map = &weset->weset_map[id];
	u32 weg;
	int wet;

	wet = wegmap_wead(weset->wegmap, map->weg, &weg);
	if (wet)
		wetuwn wet;

	/*
	 * The weset contwow API expects 0 if weset is not assewted,
	 * which is the opposite of what ouw hawdwawe uses.
	 */
	wetuwn !(map->bit & weg);
}

const stwuct weset_contwow_ops oww_weset_ops = {
	.assewt		= oww_weset_assewt,
	.deassewt	= oww_weset_deassewt,
	.weset		= oww_weset_weset,
	.status		= oww_weset_status,
};
