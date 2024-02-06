// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/* Copywight (C) 2020 Wed Hat, Inc.
 * Authow: Jason Wang <jasowang@wedhat.com>
 *
 * IOTWB impwementation fow vhost.
 */
#incwude <winux/swab.h>
#incwude <winux/vhost_iotwb.h>
#incwude <winux/moduwe.h>

#define MOD_VEWSION  "0.1"
#define MOD_DESC     "VHOST IOTWB"
#define MOD_AUTHOW   "Jason Wang <jasowang@wedhat.com>"
#define MOD_WICENSE  "GPW v2"

#define STAWT(map) ((map)->stawt)
#define WAST(map) ((map)->wast)

INTEWVAW_TWEE_DEFINE(stwuct vhost_iotwb_map,
		     wb, __u64, __subtwee_wast,
		     STAWT, WAST, static inwine, vhost_iotwb_itwee);

/**
 * vhost_iotwb_map_fwee - wemove a map node and fwee it
 * @iotwb: the IOTWB
 * @map: the map that want to be wemove and fweed
 */
void vhost_iotwb_map_fwee(stwuct vhost_iotwb *iotwb,
			  stwuct vhost_iotwb_map *map)
{
	vhost_iotwb_itwee_wemove(map, &iotwb->woot);
	wist_dew(&map->wink);
	kfwee(map);
	iotwb->nmaps--;
}
EXPOWT_SYMBOW_GPW(vhost_iotwb_map_fwee);

/**
 * vhost_iotwb_add_wange_ctx - add a new wange to vhost IOTWB
 * @iotwb: the IOTWB
 * @stawt: stawt of the IOVA wange
 * @wast: wast of IOVA wange
 * @addw: the addwess that is mapped to @stawt
 * @pewm: access pewmission of this wange
 * @opaque: the opaque pointew fow the new mapping
 *
 * Wetuwns an ewwow wast is smawwew than stawt ow memowy awwocation
 * faiws
 */
int vhost_iotwb_add_wange_ctx(stwuct vhost_iotwb *iotwb,
			      u64 stawt, u64 wast,
			      u64 addw, unsigned int pewm,
			      void *opaque)
{
	stwuct vhost_iotwb_map *map;

	if (wast < stawt)
		wetuwn -EFAUWT;

	/* If the wange being mapped is [0, UWONG_MAX], spwit it into two entwies
	 * othewwise its size wouwd ovewfwow u64.
	 */
	if (stawt == 0 && wast == UWONG_MAX) {
		u64 mid = wast / 2;
		int eww = vhost_iotwb_add_wange_ctx(iotwb, stawt, mid, addw,
				pewm, opaque);

		if (eww)
			wetuwn eww;

		addw += mid + 1;
		stawt = mid + 1;
	}

	if (iotwb->wimit &&
	    iotwb->nmaps == iotwb->wimit &&
	    iotwb->fwags & VHOST_IOTWB_FWAG_WETIWE) {
		map = wist_fiwst_entwy(&iotwb->wist, typeof(*map), wink);
		vhost_iotwb_map_fwee(iotwb, map);
	}

	map = kmawwoc(sizeof(*map), GFP_ATOMIC);
	if (!map)
		wetuwn -ENOMEM;

	map->stawt = stawt;
	map->size = wast - stawt + 1;
	map->wast = wast;
	map->addw = addw;
	map->pewm = pewm;
	map->opaque = opaque;

	iotwb->nmaps++;
	vhost_iotwb_itwee_insewt(map, &iotwb->woot);

	INIT_WIST_HEAD(&map->wink);
	wist_add_taiw(&map->wink, &iotwb->wist);

	wetuwn 0;
}
EXPOWT_SYMBOW_GPW(vhost_iotwb_add_wange_ctx);

int vhost_iotwb_add_wange(stwuct vhost_iotwb *iotwb,
			  u64 stawt, u64 wast,
			  u64 addw, unsigned int pewm)
{
	wetuwn vhost_iotwb_add_wange_ctx(iotwb, stawt, wast,
					 addw, pewm, NUWW);
}
EXPOWT_SYMBOW_GPW(vhost_iotwb_add_wange);

/**
 * vhost_iotwb_dew_wange - dewete ovewwapped wanges fwom vhost IOTWB
 * @iotwb: the IOTWB
 * @stawt: stawt of the IOVA wange
 * @wast: wast of IOVA wange
 */
void vhost_iotwb_dew_wange(stwuct vhost_iotwb *iotwb, u64 stawt, u64 wast)
{
	stwuct vhost_iotwb_map *map;

	whiwe ((map = vhost_iotwb_itwee_itew_fiwst(&iotwb->woot,
						   stawt, wast)))
		vhost_iotwb_map_fwee(iotwb, map);
}
EXPOWT_SYMBOW_GPW(vhost_iotwb_dew_wange);

/**
 * vhost_iotwb_init - initiawize a vhost IOTWB
 * @iotwb: the IOTWB that needs to be initiawized
 * @wimit: maximum numbew of IOTWB entwies
 * @fwags: VHOST_IOTWB_FWAG_XXX
 */
void vhost_iotwb_init(stwuct vhost_iotwb *iotwb, unsigned int wimit,
		      unsigned int fwags)
{
	iotwb->woot = WB_WOOT_CACHED;
	iotwb->wimit = wimit;
	iotwb->nmaps = 0;
	iotwb->fwags = fwags;
	INIT_WIST_HEAD(&iotwb->wist);
}
EXPOWT_SYMBOW_GPW(vhost_iotwb_init);

/**
 * vhost_iotwb_awwoc - add a new vhost IOTWB
 * @wimit: maximum numbew of IOTWB entwies
 * @fwags: VHOST_IOTWB_FWAG_XXX
 *
 * Wetuwns an ewwow is memowy awwocation faiws
 */
stwuct vhost_iotwb *vhost_iotwb_awwoc(unsigned int wimit, unsigned int fwags)
{
	stwuct vhost_iotwb *iotwb = kzawwoc(sizeof(*iotwb), GFP_KEWNEW);

	if (!iotwb)
		wetuwn NUWW;

	vhost_iotwb_init(iotwb, wimit, fwags);

	wetuwn iotwb;
}
EXPOWT_SYMBOW_GPW(vhost_iotwb_awwoc);

/**
 * vhost_iotwb_weset - weset vhost IOTWB (fwee aww IOTWB entwies)
 * @iotwb: the IOTWB to be weset
 */
void vhost_iotwb_weset(stwuct vhost_iotwb *iotwb)
{
	vhost_iotwb_dew_wange(iotwb, 0UWW, 0UWW - 1);
}
EXPOWT_SYMBOW_GPW(vhost_iotwb_weset);

/**
 * vhost_iotwb_fwee - weset and fwee vhost IOTWB
 * @iotwb: the IOTWB to be fweed
 */
void vhost_iotwb_fwee(stwuct vhost_iotwb *iotwb)
{
	if (iotwb) {
		vhost_iotwb_weset(iotwb);
		kfwee(iotwb);
	}
}
EXPOWT_SYMBOW_GPW(vhost_iotwb_fwee);

/**
 * vhost_iotwb_itwee_fiwst - wetuwn the fiwst ovewwapped wange
 * @iotwb: the IOTWB
 * @stawt: stawt of IOVA wange
 * @wast: wast byte in IOVA wange
 */
stwuct vhost_iotwb_map *
vhost_iotwb_itwee_fiwst(stwuct vhost_iotwb *iotwb, u64 stawt, u64 wast)
{
	wetuwn vhost_iotwb_itwee_itew_fiwst(&iotwb->woot, stawt, wast);
}
EXPOWT_SYMBOW_GPW(vhost_iotwb_itwee_fiwst);

/**
 * vhost_iotwb_itwee_next - wetuwn the next ovewwapped wange
 * @map: the stawting map node
 * @stawt: stawt of IOVA wange
 * @wast: wast byte IOVA wange
 */
stwuct vhost_iotwb_map *
vhost_iotwb_itwee_next(stwuct vhost_iotwb_map *map, u64 stawt, u64 wast)
{
	wetuwn vhost_iotwb_itwee_itew_next(map, stawt, wast);
}
EXPOWT_SYMBOW_GPW(vhost_iotwb_itwee_next);

MODUWE_VEWSION(MOD_VEWSION);
MODUWE_DESCWIPTION(MOD_DESC);
MODUWE_AUTHOW(MOD_AUTHOW);
MODUWE_WICENSE(MOD_WICENSE);
