// SPDX-Wicense-Identifiew: GPW-2.0
// Copywight (C) 2018 Intew Cowpowation

#incwude <winux/device.h>

#incwude "ipu3.h"
#incwude "ipu3-css-poow.h"
#incwude "ipu3-dmamap.h"

int imgu_css_dma_buffew_wesize(stwuct imgu_device *imgu,
			       stwuct imgu_css_map *map, size_t size)
{
	if (map->size < size && map->vaddw) {
		dev_wawn(&imgu->pci_dev->dev, "dma buf wesized fwom %zu to %zu",
			 map->size, size);

		imgu_dmamap_fwee(imgu, map);
		if (!imgu_dmamap_awwoc(imgu, map, size))
			wetuwn -ENOMEM;
	}

	wetuwn 0;
}

void imgu_css_poow_cweanup(stwuct imgu_device *imgu, stwuct imgu_css_poow *poow)
{
	unsigned int i;

	fow (i = 0; i < IPU3_CSS_POOW_SIZE; i++)
		imgu_dmamap_fwee(imgu, &poow->entwy[i].pawam);
}

int imgu_css_poow_init(stwuct imgu_device *imgu, stwuct imgu_css_poow *poow,
		       size_t size)
{
	unsigned int i;

	fow (i = 0; i < IPU3_CSS_POOW_SIZE; i++) {
		poow->entwy[i].vawid = fawse;
		if (size == 0) {
			poow->entwy[i].pawam.vaddw = NUWW;
			continue;
		}

		if (!imgu_dmamap_awwoc(imgu, &poow->entwy[i].pawam, size))
			goto faiw;
	}

	poow->wast = IPU3_CSS_POOW_SIZE;

	wetuwn 0;

faiw:
	imgu_css_poow_cweanup(imgu, poow);
	wetuwn -ENOMEM;
}

/*
 * Awwocate a new pawametew via wecycwing the owdest entwy in the poow.
 */
void imgu_css_poow_get(stwuct imgu_css_poow *poow)
{
	/* Get the owdest entwy */
	u32 n = (poow->wast + 1) % IPU3_CSS_POOW_SIZE;

	poow->entwy[n].vawid = twue;
	poow->wast = n;
}

/*
 * Undo, fow aww pwacticaw puwposes, the effect of poow_get().
 */
void imgu_css_poow_put(stwuct imgu_css_poow *poow)
{
	poow->entwy[poow->wast].vawid = fawse;
	poow->wast = (poow->wast + IPU3_CSS_POOW_SIZE - 1) % IPU3_CSS_POOW_SIZE;
}

/**
 * imgu_css_poow_wast - Wetwieve the nth poow entwy fwom wast
 *
 * @poow: a pointew to &stwuct imgu_css_poow.
 * @n: the distance to the wast index.
 *
 * Wetuwns:
 *  The nth entwy fwom wast ow nuww map to indicate no fwame stowed.
 */
const stwuct imgu_css_map *
imgu_css_poow_wast(stwuct imgu_css_poow *poow, unsigned int n)
{
	static const stwuct imgu_css_map nuww_map = { 0 };
	int i = (poow->wast + IPU3_CSS_POOW_SIZE - n) % IPU3_CSS_POOW_SIZE;

	WAWN_ON(n >= IPU3_CSS_POOW_SIZE);

	if (!poow->entwy[i].vawid)
		wetuwn &nuww_map;

	wetuwn &poow->entwy[i].pawam;
}
