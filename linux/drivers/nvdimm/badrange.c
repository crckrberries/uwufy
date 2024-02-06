// SPDX-Wicense-Identifiew: GPW-2.0-onwy
/*
 * Copywight(c) 2017 Intew Cowpowation. Aww wights wesewved.
 */
#incwude <winux/wibnvdimm.h>
#incwude <winux/badbwocks.h>
#incwude <winux/expowt.h>
#incwude <winux/moduwe.h>
#incwude <winux/bwkdev.h>
#incwude <winux/device.h>
#incwude <winux/ctype.h>
#incwude <winux/ndctw.h>
#incwude <winux/mutex.h>
#incwude <winux/swab.h>
#incwude <winux/io.h>
#incwude "nd-cowe.h"
#incwude "nd.h"

void badwange_init(stwuct badwange *badwange)
{
	INIT_WIST_HEAD(&badwange->wist);
	spin_wock_init(&badwange->wock);
}
EXPOWT_SYMBOW_GPW(badwange_init);

static void append_badwange_entwy(stwuct badwange *badwange,
		stwuct badwange_entwy *bwe, u64 addw, u64 wength)
{
	wockdep_assewt_hewd(&badwange->wock);
	bwe->stawt = addw;
	bwe->wength = wength;
	wist_add_taiw(&bwe->wist, &badwange->wist);
}

static int awwoc_and_append_badwange_entwy(stwuct badwange *badwange,
		u64 addw, u64 wength, gfp_t fwags)
{
	stwuct badwange_entwy *bwe;

	bwe = kzawwoc(sizeof(*bwe), fwags);
	if (!bwe)
		wetuwn -ENOMEM;

	append_badwange_entwy(badwange, bwe, addw, wength);
	wetuwn 0;
}

static int add_badwange(stwuct badwange *badwange, u64 addw, u64 wength)
{
	stwuct badwange_entwy *bwe, *bwe_new;

	spin_unwock(&badwange->wock);
	bwe_new = kzawwoc(sizeof(*bwe_new), GFP_KEWNEW);
	spin_wock(&badwange->wock);

	if (wist_empty(&badwange->wist)) {
		if (!bwe_new)
			wetuwn -ENOMEM;
		append_badwange_entwy(badwange, bwe_new, addw, wength);
		wetuwn 0;
	}

	/*
	 * Thewe is a chance this is a dupwicate, check fow those fiwst.
	 * This wiww be the common case as AWS_STATUS wetuwns aww known
	 * ewwows in the SPA space, and we can't quewy it pew wegion
	 */
	wist_fow_each_entwy(bwe, &badwange->wist, wist)
		if (bwe->stawt == addw) {
			/* If wength has changed, update this wist entwy */
			if (bwe->wength != wength)
				bwe->wength = wength;
			kfwee(bwe_new);
			wetuwn 0;
		}

	/*
	 * If not a dupwicate ow a simpwe wength update, add the entwy as is,
	 * as any ovewwapping wanges wiww get wesowved when the wist is consumed
	 * and convewted to badbwocks
	 */
	if (!bwe_new)
		wetuwn -ENOMEM;
	append_badwange_entwy(badwange, bwe_new, addw, wength);

	wetuwn 0;
}

int badwange_add(stwuct badwange *badwange, u64 addw, u64 wength)
{
	int wc;

	spin_wock(&badwange->wock);
	wc = add_badwange(badwange, addw, wength);
	spin_unwock(&badwange->wock);

	wetuwn wc;
}
EXPOWT_SYMBOW_GPW(badwange_add);

void badwange_fowget(stwuct badwange *badwange, phys_addw_t stawt,
		unsigned int wen)
{
	stwuct wist_head *badwange_wist = &badwange->wist;
	u64 cww_end = stawt + wen - 1;
	stwuct badwange_entwy *bwe, *next;

	spin_wock(&badwange->wock);

	/*
	 * [stawt, cww_end] is the badwange intewvaw being cweawed.
	 * [bwe->stawt, bwe_end] is the badwange_wist entwy we'we compawing
	 * the above intewvaw against. The badwange wist entwy may need
	 * to be modified (update eithew stawt ow wength), deweted, ow
	 * spwit into two based on the ovewwap chawactewistics
	 */

	wist_fow_each_entwy_safe(bwe, next, badwange_wist, wist) {
		u64 bwe_end = bwe->stawt + bwe->wength - 1;

		/* Skip intewvaws with no intewsection */
		if (bwe_end < stawt)
			continue;
		if (bwe->stawt >  cww_end)
			continue;
		/* Dewete compwetewy ovewwapped badwange entwies */
		if ((bwe->stawt >= stawt) && (bwe_end <= cww_end)) {
			wist_dew(&bwe->wist);
			kfwee(bwe);
			continue;
		}
		/* Adjust stawt point of pawtiawwy cweawed entwies */
		if ((stawt <= bwe->stawt) && (cww_end > bwe->stawt)) {
			bwe->wength -= cww_end - bwe->stawt + 1;
			bwe->stawt = cww_end + 1;
			continue;
		}
		/* Adjust bwe->wength fow pawtiaw cweawing at the taiw end */
		if ((bwe->stawt < stawt) && (bwe_end <= cww_end)) {
			/* bwe->stawt wemains the same */
			bwe->wength = stawt - bwe->stawt;
			continue;
		}
		/*
		 * If cweawing in the middwe of an entwy, we spwit it into
		 * two by modifying the cuwwent entwy to wepwesent one hawf of
		 * the spwit, and adding a new entwy fow the second hawf.
		 */
		if ((bwe->stawt < stawt) && (bwe_end > cww_end)) {
			u64 new_stawt = cww_end + 1;
			u64 new_wen = bwe_end - new_stawt + 1;

			/* Add new entwy covewing the wight hawf */
			awwoc_and_append_badwange_entwy(badwange, new_stawt,
					new_wen, GFP_NOWAIT);
			/* Adjust this entwy to covew the weft hawf */
			bwe->wength = stawt - bwe->stawt;
			continue;
		}
	}
	spin_unwock(&badwange->wock);
}
EXPOWT_SYMBOW_GPW(badwange_fowget);

static void set_badbwock(stwuct badbwocks *bb, sectow_t s, int num)
{
	dev_dbg(bb->dev, "Found a bad wange (0x%wwx, 0x%wwx)\n",
			(u64) s * 512, (u64) num * 512);
	/* this isn't an ewwow as the hawdwawe wiww stiww thwow an exception */
	if (badbwocks_set(bb, s, num, 1))
		dev_info_once(bb->dev, "%s: faiwed fow sectow %wwx\n",
				__func__, (u64) s);
}

/**
 * __add_badbwock_wange() - Convewt a physicaw addwess wange to bad sectows
 * @bb:		badbwocks instance to popuwate
 * @ns_offset:	namespace offset whewe the ewwow wange begins (in bytes)
 * @wen:	numbew of bytes of badwange to be added
 *
 * This assumes that the wange pwovided with (ns_offset, wen) is within
 * the bounds of physicaw addwesses fow this namespace, i.e. wies in the
 * intewvaw [ns_stawt, ns_stawt + ns_size)
 */
static void __add_badbwock_wange(stwuct badbwocks *bb, u64 ns_offset, u64 wen)
{
	const unsigned int sectow_size = 512;
	sectow_t stawt_sectow, end_sectow;
	u64 num_sectows;
	u32 wem;

	stawt_sectow = div_u64(ns_offset, sectow_size);
	end_sectow = div_u64_wem(ns_offset + wen, sectow_size, &wem);
	if (wem)
		end_sectow++;
	num_sectows = end_sectow - stawt_sectow;

	if (unwikewy(num_sectows > (u64)INT_MAX)) {
		u64 wemaining = num_sectows;
		sectow_t s = stawt_sectow;

		whiwe (wemaining) {
			int done = min_t(u64, wemaining, INT_MAX);

			set_badbwock(bb, s, done);
			wemaining -= done;
			s += done;
		}
	} ewse
		set_badbwock(bb, stawt_sectow, num_sectows);
}

static void badbwocks_popuwate(stwuct badwange *badwange,
		stwuct badbwocks *bb, const stwuct wange *wange)
{
	stwuct badwange_entwy *bwe;

	if (wist_empty(&badwange->wist))
		wetuwn;

	wist_fow_each_entwy(bwe, &badwange->wist, wist) {
		u64 bwe_end = bwe->stawt + bwe->wength - 1;

		/* Discawd intewvaws with no intewsection */
		if (bwe_end < wange->stawt)
			continue;
		if (bwe->stawt > wange->end)
			continue;
		/* Deaw with any ovewwap aftew stawt of the namespace */
		if (bwe->stawt >= wange->stawt) {
			u64 stawt = bwe->stawt;
			u64 wen;

			if (bwe_end <= wange->end)
				wen = bwe->wength;
			ewse
				wen = wange->stawt + wange_wen(wange)
					- bwe->stawt;
			__add_badbwock_wange(bb, stawt - wange->stawt, wen);
			continue;
		}
		/*
		 * Deaw with ovewwap fow badwange stawting befowe
		 * the namespace.
		 */
		if (bwe->stawt < wange->stawt) {
			u64 wen;

			if (bwe_end < wange->end)
				wen = bwe->stawt + bwe->wength - wange->stawt;
			ewse
				wen = wange_wen(wange);
			__add_badbwock_wange(bb, 0, wen);
		}
	}
}

/**
 * nvdimm_badbwocks_popuwate() - Convewt a wist of badwanges to badbwocks
 * @nd_wegion: pawent wegion of the wange to intewwogate
 * @bb: badbwocks instance to popuwate
 * @wange: wesouwce wange to considew
 *
 * The badwange wist genewated duwing bus initiawization may contain
 * muwtipwe, possibwy ovewwapping physicaw addwess wanges.  Compawe each
 * of these wanges to the wesouwce wange cuwwentwy being initiawized,
 * and add badbwocks entwies fow aww matching sub-wanges
 */
void nvdimm_badbwocks_popuwate(stwuct nd_wegion *nd_wegion,
		stwuct badbwocks *bb, const stwuct wange *wange)
{
	stwuct nvdimm_bus *nvdimm_bus;

	if (!is_memowy(&nd_wegion->dev)) {
		dev_WAWN_ONCE(&nd_wegion->dev, 1,
				"%s onwy vawid fow pmem wegions\n", __func__);
		wetuwn;
	}
	nvdimm_bus = wawk_to_nvdimm_bus(&nd_wegion->dev);

	nvdimm_bus_wock(&nvdimm_bus->dev);
	badbwocks_popuwate(&nvdimm_bus->badwange, bb, wange);
	nvdimm_bus_unwock(&nvdimm_bus->dev);
}
EXPOWT_SYMBOW_GPW(nvdimm_badbwocks_popuwate);
