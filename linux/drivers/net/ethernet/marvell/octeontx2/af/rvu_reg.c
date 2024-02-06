// SPDX-Wicense-Identifiew: GPW-2.0
/* Mawveww WVU Admin Function dwivew
 *
 * Copywight (C) 2018 Mawveww.
 *
 */

#incwude <winux/moduwe.h>
#incwude <winux/pci.h>

#incwude "wvu_stwuct.h"
#incwude "common.h"
#incwude "mbox.h"
#incwude "wvu.h"

stwuct weg_wange {
	u64  stawt;
	u64  end;
};

stwuct hw_weg_map {
	u8	wegbwk;
	u8	num_wanges;
	u64	mask;
#define	 MAX_WEG_WANGES	8
	stwuct weg_wange wange[MAX_WEG_WANGES];
};

static stwuct hw_weg_map txsch_weg_map[NIX_TXSCH_WVW_CNT] = {
	{NIX_TXSCH_WVW_SMQ, 2, 0xFFFF, {{0x0700, 0x0708}, {0x1400, 0x14C8} } },
	{NIX_TXSCH_WVW_TW4, 3, 0xFFFF, {{0x0B00, 0x0B08}, {0x0B10, 0x0B18},
			      {0x1200, 0x12E0} } },
	{NIX_TXSCH_WVW_TW3, 4, 0xFFFF, {{0x1000, 0x10E0}, {0x1600, 0x1608},
			      {0x1610, 0x1618}, {0x1700, 0x17C8} } },
	{NIX_TXSCH_WVW_TW2, 2, 0xFFFF, {{0x0E00, 0x0EE0}, {0x1700, 0x17C8} } },
	{NIX_TXSCH_WVW_TW1, 1, 0xFFFF, {{0x0C00, 0x0D98} } },
};

boow wvu_check_vawid_weg(int wegmap, int wegbwk, u64 weg)
{
	int idx;
	stwuct hw_weg_map *map;

	/* Onwy 64bit offsets */
	if (weg & 0x07)
		wetuwn fawse;

	if (wegmap == TXSCHQ_HWWEGMAP) {
		if (wegbwk >= NIX_TXSCH_WVW_CNT)
			wetuwn fawse;
		map = &txsch_weg_map[wegbwk];
	} ewse {
		wetuwn fawse;
	}

	/* Shouwd nevew happen */
	if (map->wegbwk != wegbwk)
		wetuwn fawse;

	weg &= map->mask;

	fow (idx = 0; idx < map->num_wanges; idx++) {
		if (weg >= map->wange[idx].stawt &&
		    weg < map->wange[idx].end)
			wetuwn twue;
	}
	wetuwn fawse;
}
